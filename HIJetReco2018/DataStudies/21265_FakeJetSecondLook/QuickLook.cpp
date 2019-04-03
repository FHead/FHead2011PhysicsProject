#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TF1.h"
#include "TLatex.h"

#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "Messenger.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputBase             = CL.Get("OutputBase", "Result");
   string JetTreeName            = CL.Get("Tree", "akCs4PFJetAnalyzer/t");
   bool CheckFraction            = CL.GetBool("CheckFraction", true);
   bool ReducedEta               = CL.GetBool("ReducedEta", false);
   bool PrintDebug               = CL.GetBool("PrintDebug", false);
   double MinPTForTrack          = CL.GetDouble("MinPTForTrack", 50);

   double MaxEta = 2.5;
   if(ReducedEta == true)
      MaxEta = 2.2;

   string Function = "(ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], 0) - exp(-[0]*(x-[1])+[0]*[0]*[2]*[2]/2)*ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], [0]*[0]*[2]*[2])) * ([3] - [4]) + [4]";

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Jet quick look");

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HN("HN", "", 1, 0, 1);
   TH2D HJetEtaPhiPT30("HJetEtaPhiPT30", "PT > 30;eta;phi", 75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT50("HJetEtaPhiPT50", "PT > 50;eta;phi", 75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT70("HJetEtaPhiPT70", "PT > 70;eta;phi", 75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT100("HJetEtaPhiPT100", "PT > 100;eta;phi", 75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT70FailL156("HJetEtaPhiPT70FailL156", "PT > 70, fail L1_SingleJet56;eta;phi",
      75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT80FailL156("HJetEtaPhiPT80FailL156", "PT > 80, fail L1_SingleJet56;eta;phi",
      75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT100FailL156("HJetEtaPhiPT100FailL156", "PT > 100, fail L1_SingleJet56;eta;phi",
      75, -MaxEta, MaxEta, 75, -M_PI, M_PI);
   TH2D HJetEtaPhiPT120FailL156("HJetEtaPhiPT120FailL156", "PT > 120, fail L1_SingleJet56;eta;phi",
      75, -MaxEta, MaxEta, 75, -M_PI, M_PI);

   TH1D HJetPT("HJetPT", "Leading jet in full range;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN15P15("HJetPT_EtaN15P15", "Leading jet in |eta| < 1.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25P25("HJetPT_EtaN25P25", "Leading jet in |eta| < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN00P25("HJetPT_EtaN00P25", "Leading jet in 0 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25P00("HJetPT_EtaN25P00", "Leading jet in -2.5 < eta < 0;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaP15P25("HJetPT_EtaP15P25", "Leading jet in 1.5 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25N15("HJetPT_EtaN25N15", "Leading jet in -2.5 < eta < -1.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156("HJetPTPassL156", "Leading jet in full range;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN15P15("HJetPTPassL156_EtaN15P15", "Leading jet in |eta| < 1.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25P25("HJetPTPassL156_EtaN25P25", "Leading jet in |eta| < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN00P25("HJetPTPassL156_EtaN00P25", "Leading jet in 0 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25P00("HJetPTPassL156_EtaN25P00", "Leading jet in -2.5 < eta < 0;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaP15P25("HJetPTPassL156_EtaP15P25", "Leading jet in 1.5 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25N15("HJetPTPassL156_EtaN25N15", "Leading jet in -2.5 < eta < -1.5;p_{T};", 100, 0, 200);

   TH2D HJetPTVsRawPT("HJetPTVsRawPT", "|#eta| < 2.5;Jet PT;Raw PT", 100, 0, 200, 100, 0, 200);
   TH2D HRawPTVsJEC("HRawPTVsJEC", "|#eta| < 2.5;Raw PT;JEC", 100, 0, 200, 100, 0, 2);

   TH1D HAllJetPT_EtaN25N15("HAllJetPT_EtaN25N15", "Jet PT, -2.5 < #eta < -1.5;p_{T}", 100, 0, 200);
   TH1D HAllJetPT_EtaN15P15("HAllJetPT_EtaN15P15", "Jet PT, -1.5 < #eta < 1.5;p_{T}", 100, 0, 200);
   TH1D HAllJetPT_EtaP15P25("HAllJetPT_EtaP15P25", "Jet PT, 1.5 < #eta < 2.5;p_{T}", 100, 0, 200);

   TH1D HJetCHF_PT50_EtaN25N15("HJetCHF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT50_EtaN15P15("HJetCHF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT50_EtaP15P25("HJetCHF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CHF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaN25N15("HJetCEF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaN15P15("HJetCEF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaP15P25("HJetCEF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CEF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaN25N15("HJetNHF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaN15P15("HJetNHF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaP15P25("HJetNHF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NHF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaN25N15("HJetNEF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaN15P15("HJetNEF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaP15P25("HJetNEF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NEF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaN25N15("HJetMUF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaN15P15("HJetMUF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaP15P25("HJetMUF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;MUF;", 100, 0, 1);
   TH1D HJetCH_PT50_EtaN25N15("HJetCH_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT50_EtaN15P15("HJetCH_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT50_EtaP15P25("HJetCH_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CH;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaN25N15("HJetCE_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaN15P15("HJetCE_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaP15P25("HJetCE_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CE;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaN25N15("HJetNH_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaN15P15("HJetNH_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaP15P25("HJetNH_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NH;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaN25N15("HJetNE_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaN15P15("HJetNE_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaP15P25("HJetNE_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NE;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaN25N15("HJetMU_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaN15P15("HJetMU_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaP15P25("HJetMU_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;MU;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaN25N15("HJetHad_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaN15P15("HJetHad_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaP15P25("HJetHad_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;Had;", 100, 0, 200);
   
   TH1D HJetCHF_PT70_EtaN25N15("HJetCHF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT70_EtaN15P15("HJetCHF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT70_EtaP15P25("HJetCHF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CHF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaN25N15("HJetCEF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaN15P15("HJetCEF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaP15P25("HJetCEF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CEF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaN25N15("HJetNHF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaN15P15("HJetNHF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaP15P25("HJetNHF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NHF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaN25N15("HJetNEF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaN15P15("HJetNEF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaP15P25("HJetNEF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NEF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaN25N15("HJetMUF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaN15P15("HJetMUF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaP15P25("HJetMUF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;MUF;", 100, 0, 1);
   TH1D HJetCH_PT70_EtaN25N15("HJetCH_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT70_EtaN15P15("HJetCH_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT70_EtaP15P25("HJetCH_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CH;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaN25N15("HJetCE_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaN15P15("HJetCE_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaP15P25("HJetCE_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CE;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaN25N15("HJetNH_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaN15P15("HJetNH_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaP15P25("HJetNH_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NH;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaN25N15("HJetNE_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaN15P15("HJetNE_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaP15P25("HJetNE_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NE;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaN25N15("HJetMU_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaN15P15("HJetMU_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaP15P25("HJetMU_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;MU;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaN25N15("HJetHad_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaN15P15("HJetHad_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaP15P25("HJetHad_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;Had;", 100, 0, 200);

   TH1D HCaloPFMatchDR_PassL156("HCaloPFMatchDR_PassL156", ";#DeltaR;", 100, 0, 1.0);
   TH1D HCaloPFMatchDR_FailL156("HCaloPFMatchDR_FailL156", ";#DeltaR;", 100, 0, 1.0);

   TH1D HTrackAlgo_PT70_Matched("HTrackAlgo_PT70_Matched",
      "Track algo, Jet PT > 70, pass L1_SingleJet56 and matched", 64, 0, 64);
   TH1D HTrackAlgo_PT70_NonMatch("HTrackAlgo_PT70_NonMatch",
      "Track algo, Jet PT > 70, fail L1_SingleJet56 and no-match", 64, 0, 64);
   TH1D HTrackPT_Algo6_PT70_Matched("HTrackPT_Algo6_PT70_Matched",
      "Track PT, Algo 6, Jet PT > 70, pass L1_SingleJet56 and matched", 100, 0, 25);
   TH1D HTrackPT_Algo6_PT70_NonMatch("HTrackPT_Algo6_PT70_NonMatch",
      "Track PT, Algo 6, Jet PT > 70, fail L1_SingleJet56 and no-match", 100, 0, 25);
   TH1D HTrackMVA_Algo6_PT70_Matched("HTrackMVA_Algo6_PT70_Matched",
      "Track MVA, Algo 6, Jet PT > 70, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6_PT70_NonMatch("HTrackMVA_Algo6_PT70_NonMatch",
      "Track MVA, Algo 6, Jet PT > 70, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT70_Matched("HTrackMVA_Algo6MinPT_PT70_Matched",
      "Track MVA, Algo 6, Jet PT > 70, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT70_NonMatch("HTrackMVA_Algo6MinPT_PT70_NonMatch",
      "Track MVA, Algo 6, Jet PT > 70, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT70_Matched("HTrackPTVsMVA_Algo6_PT70_Matched",
      "Track PT Vs MVA, Algo 6, Jet PT > 70, pass L1_SingleJet56 and matched", 100, 0, 4, 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT70_NonMatch("HTrackPTVsMVA_Algo6_PT70_NonMatch",
      "Track PT Vs MVA, Algo 6, Jet PT > 70, fail L1_SingleJet56 and no-match", 100, 0, 4, 100, 0.88, 1.02);
   TH1D HTrackAlgo_PT80_Matched("HTrackAlgo_PT80_Matched",
      "Track algo, Jet PT > 80, pass L1_SingleJet56 and matched", 64, 0, 64);
   TH1D HTrackAlgo_PT80_NonMatch("HTrackAlgo_PT80_NonMatch",
      "Track algo, Jet PT > 80, fail L1_SingleJet56 and no-match", 64, 0, 64);
   TH1D HTrackPT_Algo6_PT80_Matched("HTrackPT_Algo6_PT80_Matched",
      "Track PT, Algo 6, Jet PT > 80, pass L1_SingleJet56 and matched", 100, 0, 25);
   TH1D HTrackPT_Algo6_PT80_NonMatch("HTrackPT_Algo6_PT80_NonMatch",
      "Track PT, Algo 6, Jet PT > 80, fail L1_SingleJet56 and no-match", 100, 0, 25);
   TH1D HTrackMVA_Algo6_PT80_Matched("HTrackMVA_Algo6_PT80_Matched",
      "Track MVA, Algo 6, Jet PT > 80, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6_PT80_NonMatch("HTrackMVA_Algo6_PT80_NonMatch",
      "Track MVA, Algo 6, Jet PT > 80, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT80_Matched("HTrackMVA_Algo6MinPT_PT80_Matched",
      "Track MVA, Algo 6, Jet PT > 80, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT80_NonMatch("HTrackMVA_Algo6MinPT_PT80_NonMatch",
      "Track MVA, Algo 6, Jet PT > 80, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT80_Matched("HTrackPTVsMVA_Algo6_PT80_Matched",
      "Track PT Vs MVA, Algo 6, Jet PT > 80, pass L1_SingleJet56 and matched", 100, 0, 4, 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT80_NonMatch("HTrackPTVsMVA_Algo6_PT80_NonMatch",
      "Track PT Vs MVA, Algo 6, Jet PT > 80, fail L1_SingleJet56 and no-match", 100, 0, 4, 100, 0.88, 1.02);
   TH1D HTrackAlgo_PT100_Matched("HTrackAlgo_PT100_Matched",
      "Track algo, Jet PT > 100, pass L1_SingleJet56 and matched", 64, 0, 64);
   TH1D HTrackAlgo_PT100_NonMatch("HTrackAlgo_PT100_NonMatch",
      "Track algo, Jet PT > 100, fail L1_SingleJet56 and no-match", 64, 0, 64);
   TH1D HTrackPT_Algo6_PT100_Matched("HTrackPT_Algo6_PT100_Matched",
      "Track PT, Algo 6, Jet PT > 100, pass L1_SingleJet56 and matched", 100, 0, 25);
   TH1D HTrackPT_Algo6_PT100_NonMatch("HTrackPT_Algo6_PT100_NonMatch",
      "Track PT, Algo 6, Jet PT > 100, fail L1_SingleJet56 and no-match", 100, 0, 25);
   TH1D HTrackMVA_Algo6_PT100_Matched("HTrackMVA_Algo6_PT100_Matched",
      "Track MVA, Algo 6, Jet PT > 100, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6_PT100_NonMatch("HTrackMVA_Algo6_PT100_NonMatch",
      "Track MVA, Algo 6, Jet PT > 100, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT100_Matched("HTrackMVA_Algo6MinPT_PT100_Matched",
      "Track MVA, Algo 6, Jet PT > 100, pass L1_SingleJet56 and matched", 100, 0.88, 1.02);
   TH1D HTrackMVA_Algo6MinPT_PT100_NonMatch("HTrackMVA_Algo6MinPT_PT100_NonMatch",
      "Track MVA, Algo 6, Jet PT > 100, fail L1_SingleJet56 and no-match", 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT100_Matched("HTrackPTVsMVA_Algo6_PT100_Matched",
      "Track PT Vs MVA, Algo 6, Jet PT > 100, pass L1_SingleJet56 and matched", 100, 0, 4, 100, 0.88, 1.02);
   TH2D HTrackPTVsMVA_Algo6_PT100_NonMatch("HTrackPTVsMVA_Algo6_PT100_NonMatch",
      "Track PT Vs MVA, Algo 6, Jet PT > 100, fail L1_SingleJet56 and no-match", 100, 0, 4, 100, 0.88, 1.02);

   TH1D HTrackAlgo6Fraction_PT70_Matched("HTrackAlgo6Fraction_PT70_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT80_Matched("HTrackAlgo6Fraction_PT80_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT100_Matched("HTrackAlgo6Fraction_PT100_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT70_NonMatch("HTrackAlgo6Fraction_PT70_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT80_NonMatch("HTrackAlgo6Fraction_PT80_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT100_NonMatch("HTrackAlgo6Fraction_PT100_NonMatch", "", 100, 0, 1.0);
   
   TH1D HTrackAlgo6Fraction_PT70_PassL156("HTrackAlgo6Fraction_PT70_PassL156", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT80_PassL156("HTrackAlgo6Fraction_PT80_PassL156", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT100_PassL156("HTrackAlgo6Fraction_PT100_PassL156", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT70_FailL156("HTrackAlgo6Fraction_PT70_FailL156", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT80_FailL156("HTrackAlgo6Fraction_PT80_FailL156", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_PT100_FailL156("HTrackAlgo6Fraction_PT100_FailL156", "", 100, 0, 1.0);
   
   TH1D HTrackAlgo6Fraction_MinPT_PT70_Matched("HTrackAlgo6Fraction_MinPT_PT70_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MinPT_PT80_Matched("HTrackAlgo6Fraction_MinPT_PT80_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MinPT_PT100_Matched("HTrackAlgo6Fraction_MinPT_PT100_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MinPT_PT70_NonMatch("HTrackAlgo6Fraction_MinPT_PT70_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MinPT_PT80_NonMatch("HTrackAlgo6Fraction_MinPT_PT80_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MinPT_PT100_NonMatch("HTrackAlgo6Fraction_MinPT_PT100_NonMatch", "", 100, 0, 1.0);
   
   TH1D HTrackAlgo6Fraction_MVA095_PT70_Matched("HTrackAlgo6Fraction_MVA095_PT70_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA095_PT80_Matched("HTrackAlgo6Fraction_MVA095_PT80_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA095_PT100_Matched("HTrackAlgo6Fraction_MVA095_PT100_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA095_PT70_NonMatch("HTrackAlgo6Fraction_MVA095_PT70_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA095_PT80_NonMatch("HTrackAlgo6Fraction_MVA095_PT80_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA095_PT100_NonMatch("HTrackAlgo6Fraction_MVA095_PT100_NonMatch", "", 100, 0, 1.0);

   TH1D HTrackAlgo6Fraction_MVA098_PT70_Matched("HTrackAlgo6Fraction_MVA098_PT70_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA098_PT80_Matched("HTrackAlgo6Fraction_MVA098_PT80_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA098_PT100_Matched("HTrackAlgo6Fraction_MVA098_PT100_Matched", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA098_PT70_NonMatch("HTrackAlgo6Fraction_MVA098_PT70_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA098_PT80_NonMatch("HTrackAlgo6Fraction_MVA098_PT80_NonMatch", "", 100, 0, 1.0);
   TH1D HTrackAlgo6Fraction_MVA098_PT100_NonMatch("HTrackAlgo6Fraction_MVA098_PT100_NonMatch", "", 100, 0, 1.0);

   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched("HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched", "PT > 70, pass L156, matched, Algo6/Track < 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch("HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch", "PT > 70, fail L156, no match, Algo6/Track < 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156("HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156", "PT > 70, pass L156, Algo6/Track < 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156("HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156", "PT > 70, fail L156, Algo6/Track < 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched("HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched", "PT > 70, Pass l156, matched, Algo6/Track > 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch("HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch", "PT > 70, fail L156, no match, Algo6/Track > 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156("HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156", "PT > 70, pass L156, Algo6/Track > 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156("HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156", "PT > 70, fail L156, Algo6/Track > 0.2;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   
   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT50("HJetEtaPhi_GoodTrackAlgoFraction_PT50", "PT > 50, Algo6/Track < 0.25;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT50("HJetEtaPhi_BadTrackAlgoFraction_PT50", "PT > 50, Algo6/Track > 0.25;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_GoodTrackAlgoFraction_PT70("HJetEtaPhi_GoodTrackAlgoFraction_PT70", "PT > 70, Algo6/Track < 0.25;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_BadTrackAlgoFraction_PT70("HJetEtaPhi_BadTrackAlgoFraction_PT70", "PT > 70, Algo6/Track > 0.25;eta;phi", 100, -MaxEta, MaxEta, 100, -M_PI, M_PI);

   TH1D HPFPT_ID1_EtaN25N15("HPFPT_ID1_EtaN25N15", "PF Candidate PT, ID = 1, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID1_EtaN15P15("HPFPT_ID1_EtaN15P15", "PF Candidate PT, ID = 1, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID1_EtaP15P25("HPFPT_ID1_EtaP15P25", "PF Candidate PT, ID = 1, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID2_EtaN25N15("HPFPT_ID2_EtaN25N15", "PF Candidate PT, ID = 2, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID2_EtaN15P15("HPFPT_ID2_EtaN15P15", "PF Candidate PT, ID = 2, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID2_EtaP15P25("HPFPT_ID2_EtaP15P25", "PF Candidate PT, ID = 2, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID3_EtaN25N15("HPFPT_ID3_EtaN25N15", "PF Candidate PT, ID = 3, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID3_EtaN15P15("HPFPT_ID3_EtaN15P15", "PF Candidate PT, ID = 3, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID3_EtaP15P25("HPFPT_ID3_EtaP15P25", "PF Candidate PT, ID = 3, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID4_EtaN25N15("HPFPT_ID4_EtaN25N15", "PF Candidate PT, ID = 4, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID4_EtaN15P15("HPFPT_ID4_EtaN15P15", "PF Candidate PT, ID = 4, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID4_EtaP15P25("HPFPT_ID4_EtaP15P25", "PF Candidate PT, ID = 4, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID5_EtaN25N15("HPFPT_ID5_EtaN25N15", "PF Candidate PT, ID = 5, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID5_EtaN15P15("HPFPT_ID5_EtaN15P15", "PF Candidate PT, ID = 5, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID5_EtaP15P25("HPFPT_ID5_EtaP15P25", "PF Candidate PT, ID = 5, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID6_EtaN25N15("HPFPT_ID6_EtaN25N15", "PF Candidate PT, ID = 6, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID6_EtaN15P15("HPFPT_ID6_EtaN15P15", "PF Candidate PT, ID = 6, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID6_EtaP15P25("HPFPT_ID6_EtaP15P25", "PF Candidate PT, ID = 6, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID7_EtaN25N15("HPFPT_ID7_EtaN25N15", "PF Candidate PT, ID = 7, -2.5 < #eta < -1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID7_EtaN15P15("HPFPT_ID7_EtaN15P15", "PF Candidate PT, ID = 7, -1.5 < #eta < 1.5;p_{T}", 100, 0, 75);
   TH1D HPFPT_ID7_EtaP15P25("HPFPT_ID7_EtaP15P25", "PF Candidate PT, ID = 7, 1.5 < #eta < 2.5;p_{T}", 100, 0, 75);

   TH2D HPFEtaPhi_ID1_PT05("HPFEtaPhi_ID1_PT05", "ID = 1, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT05("HPFEtaPhi_ID2_PT05", "ID = 2, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT05("HPFEtaPhi_ID3_PT05", "ID = 3, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT05("HPFEtaPhi_ID4_PT05", "ID = 4, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT05("HPFEtaPhi_ID5_PT05", "ID = 5, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT05("HPFEtaPhi_ID6_PT05", "ID = 6, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT05("HPFEtaPhi_ID7_PT05", "ID = 7, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT10("HPFEtaPhi_ID1_PT10", "ID = 1, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT10("HPFEtaPhi_ID2_PT10", "ID = 2, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT10("HPFEtaPhi_ID3_PT10", "ID = 3, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT10("HPFEtaPhi_ID4_PT10", "ID = 4, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT10("HPFEtaPhi_ID5_PT10", "ID = 5, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT10("HPFEtaPhi_ID6_PT10", "ID = 6, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT10("HPFEtaPhi_ID7_PT10", "ID = 7, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT20("HPFEtaPhi_ID1_PT20", "ID = 1, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT20("HPFEtaPhi_ID2_PT20", "ID = 2, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT20("HPFEtaPhi_ID3_PT20", "ID = 3, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT20("HPFEtaPhi_ID4_PT20", "ID = 4, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT20("HPFEtaPhi_ID5_PT20", "ID = 5, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT20("HPFEtaPhi_ID6_PT20", "ID = 6, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT20("HPFEtaPhi_ID7_PT20", "ID = 7, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT50("HPFEtaPhi_ID1_PT50", "ID = 1, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT50("HPFEtaPhi_ID2_PT50", "ID = 2, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT50("HPFEtaPhi_ID3_PT50", "ID = 3, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT50("HPFEtaPhi_ID4_PT50", "ID = 4, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT50("HPFEtaPhi_ID5_PT50", "ID = 5, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT50("HPFEtaPhi_ID6_PT50", "ID = 6, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT50("HPFEtaPhi_ID7_PT50", "ID = 7, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT100("HPFEtaPhi_ID1_PT100", "ID = 1, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT100("HPFEtaPhi_ID2_PT100", "ID = 2, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT100("HPFEtaPhi_ID3_PT100", "ID = 3, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT100("HPFEtaPhi_ID4_PT100", "ID = 4, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT100("HPFEtaPhi_ID5_PT100", "ID = 5, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT100("HPFEtaPhi_ID6_PT100", "ID = 6, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT100("HPFEtaPhi_ID7_PT100", "ID = 7, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT200("HPFEtaPhi_ID1_PT200", "ID = 1, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT200("HPFEtaPhi_ID2_PT200", "ID = 2, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT200("HPFEtaPhi_ID3_PT200", "ID = 3, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT200("HPFEtaPhi_ID4_PT200", "ID = 4, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT200("HPFEtaPhi_ID5_PT200", "ID = 5, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT200("HPFEtaPhi_ID6_PT200", "ID = 6, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT200("HPFEtaPhi_ID7_PT200", "ID = 7, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID1_PT500("HPFEtaPhi_ID1_PT500", "ID = 1, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID2_PT500("HPFEtaPhi_ID2_PT500", "ID = 2, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID3_PT500("HPFEtaPhi_ID3_PT500", "ID = 3, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID4_PT500("HPFEtaPhi_ID4_PT500", "ID = 4, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID5_PT500("HPFEtaPhi_ID5_PT500", "ID = 5, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID6_PT500("HPFEtaPhi_ID6_PT500", "ID = 6, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_ID7_PT500("HPFEtaPhi_ID7_PT500", "ID = 7, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   TH2D HPFEtaPhi_Peripheral_ID1_PT05("HPFEtaPhi_Peripheral_ID1_PT05", "ID = 1, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT05("HPFEtaPhi_Peripheral_ID2_PT05", "ID = 2, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT05("HPFEtaPhi_Peripheral_ID3_PT05", "ID = 3, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT05("HPFEtaPhi_Peripheral_ID4_PT05", "ID = 4, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT05("HPFEtaPhi_Peripheral_ID5_PT05", "ID = 5, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT05("HPFEtaPhi_Peripheral_ID6_PT05", "ID = 6, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT05("HPFEtaPhi_Peripheral_ID7_PT05", "ID = 7, PT > 0.5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT10("HPFEtaPhi_Peripheral_ID1_PT10", "ID = 1, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT10("HPFEtaPhi_Peripheral_ID2_PT10", "ID = 2, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT10("HPFEtaPhi_Peripheral_ID3_PT10", "ID = 3, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT10("HPFEtaPhi_Peripheral_ID4_PT10", "ID = 4, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT10("HPFEtaPhi_Peripheral_ID5_PT10", "ID = 5, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT10("HPFEtaPhi_Peripheral_ID6_PT10", "ID = 6, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT10("HPFEtaPhi_Peripheral_ID7_PT10", "ID = 7, PT > 1.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT20("HPFEtaPhi_Peripheral_ID1_PT20", "ID = 1, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT20("HPFEtaPhi_Peripheral_ID2_PT20", "ID = 2, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT20("HPFEtaPhi_Peripheral_ID3_PT20", "ID = 3, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT20("HPFEtaPhi_Peripheral_ID4_PT20", "ID = 4, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT20("HPFEtaPhi_Peripheral_ID5_PT20", "ID = 5, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT20("HPFEtaPhi_Peripheral_ID6_PT20", "ID = 6, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT20("HPFEtaPhi_Peripheral_ID7_PT20", "ID = 7, PT > 2.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT50("HPFEtaPhi_Peripheral_ID1_PT50", "ID = 1, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT50("HPFEtaPhi_Peripheral_ID2_PT50", "ID = 2, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT50("HPFEtaPhi_Peripheral_ID3_PT50", "ID = 3, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT50("HPFEtaPhi_Peripheral_ID4_PT50", "ID = 4, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT50("HPFEtaPhi_Peripheral_ID5_PT50", "ID = 5, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT50("HPFEtaPhi_Peripheral_ID6_PT50", "ID = 6, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT50("HPFEtaPhi_Peripheral_ID7_PT50", "ID = 7, PT > 5.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT100("HPFEtaPhi_Peripheral_ID1_PT100", "ID = 1, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT100("HPFEtaPhi_Peripheral_ID2_PT100", "ID = 2, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT100("HPFEtaPhi_Peripheral_ID3_PT100", "ID = 3, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT100("HPFEtaPhi_Peripheral_ID4_PT100", "ID = 4, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT100("HPFEtaPhi_Peripheral_ID5_PT100", "ID = 5, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT100("HPFEtaPhi_Peripheral_ID6_PT100", "ID = 6, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT100("HPFEtaPhi_Peripheral_ID7_PT100", "ID = 7, PT > 10.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT200("HPFEtaPhi_Peripheral_ID1_PT200", "ID = 1, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT200("HPFEtaPhi_Peripheral_ID2_PT200", "ID = 2, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT200("HPFEtaPhi_Peripheral_ID3_PT200", "ID = 3, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT200("HPFEtaPhi_Peripheral_ID4_PT200", "ID = 4, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT200("HPFEtaPhi_Peripheral_ID5_PT200", "ID = 5, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT200("HPFEtaPhi_Peripheral_ID6_PT200", "ID = 6, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT200("HPFEtaPhi_Peripheral_ID7_PT200", "ID = 7, PT > 20.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID1_PT500("HPFEtaPhi_Peripheral_ID1_PT500", "ID = 1, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID2_PT500("HPFEtaPhi_Peripheral_ID2_PT500", "ID = 2, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID3_PT500("HPFEtaPhi_Peripheral_ID3_PT500", "ID = 3, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID4_PT500("HPFEtaPhi_Peripheral_ID4_PT500", "ID = 4, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID5_PT500("HPFEtaPhi_Peripheral_ID5_PT500", "ID = 5, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID6_PT500("HPFEtaPhi_Peripheral_ID6_PT500", "ID = 6, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HPFEtaPhi_Peripheral_ID7_PT500("HPFEtaPhi_Peripheral_ID7_PT500", "ID = 7, PT > 50.0;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      string CaloTreeName = "akPu4CaloJetAnalyzer/t";
      if(CaloTreeName == JetTreeName)
         CaloTreeName = "NULL";

      HiEventTreeMessenger MHiEvent(InputFile);
      JetTreeMessenger MJet(InputFile, JetTreeName);
      JetTreeMessenger MCaloJet(InputFile, CaloTreeName);
      TriggerTreeMessenger MHLT(InputFile);
      TrackTreeMessenger MTrack(InputFile);
      PFTreeMessenger MPF(InputFile);
      SkimTreeMessenger MSkim(InputFile);

      if(MHiEvent.Tree == nullptr)
      {
         InputFile.Close();
         continue;
      }

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

         MHiEvent.GetEntry(iE);
         MJet.GetEntry(iE);
         MCaloJet.GetEntry(iE);
         MHLT.GetEntry(iE);
         MTrack.GetEntry(iE);
         MPF.GetEntry(iE);
         MSkim.GetEntry(iE);

         if(MSkim.HBHENoiseRun2Loose == false)
            continue;

         bool GoodLumi = false;
         if(MHiEvent.Run == 327400 && (MHiEvent.Lumi >= 38 && MHiEvent.Lumi <= 578))
            GoodLumi = true;
         if(MHiEvent.Run == 327402 && (MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 294))
            GoodLumi = true;
         if(MHiEvent.Run == 327430 && (MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 497))
            GoodLumi = true;
         if(MHiEvent.Run == 327430 && (MHiEvent.Lumi >= 499 && MHiEvent.Lumi <= 1092))
            GoodLumi = true;
         if(MHiEvent.Run == 327462 && (MHiEvent.Lumi >= 42 && MHiEvent.Lumi <= 320))
            GoodLumi = true;
         if(MHiEvent.Run == 327524)
            GoodLumi = true;
         if(GoodLumi == false)
            continue;

         HN.Fill(0);

         int BestJetIndex = -1;

         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            if(MJet.JetPT[iJ] > 50)
            {
               if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               {
                  HJetCHF_PT50_EtaN25N15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaN25N15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaN25N15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaN25N15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaN25N15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaN25N15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaN25N15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaN25N15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaN25N15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaN25N15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaN25N15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               {
                  HJetCHF_PT50_EtaN15P15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaN15P15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaN15P15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaN15P15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaN15P15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaN15P15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaN15P15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaN15P15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaN15P15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaN15P15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaN15P15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               {
                  HJetCHF_PT50_EtaP15P25.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaP15P25.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaP15P25.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaP15P25.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaP15P25.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaP15P25.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaP15P25.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaP15P25.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaP15P25.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaP15P25.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaP15P25.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
            }
            if(MJet.JetPT[iJ] > 70)
            {
               if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               {
                  HJetCHF_PT70_EtaN25N15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaN25N15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaN25N15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaN25N15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaN25N15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaN25N15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaN25N15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaN25N15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaN25N15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaN25N15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaN25N15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               {
                  HJetCHF_PT70_EtaN15P15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaN15P15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaN15P15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaN15P15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaN15P15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaN15P15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaN15P15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaN15P15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaN15P15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaN15P15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaN15P15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               {
                  HJetCHF_PT70_EtaP15P25.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaP15P25.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaP15P25.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaP15P25.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaP15P25.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaP15P25.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaP15P25.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaP15P25.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaP15P25.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaP15P25.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaP15P25.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
            }

            if(CheckFraction == true)
            {
               if(MJet.JetPFMUF[iJ] > 0.01)
                  continue;
               if(MJet.JetPFCHF[iJ] < 0.01)
                  continue;
               if(MJet.JetPFNHF[iJ] < 0.01)
                  continue;
            }

            if(fabs(MJet.JetEta[iJ]) < MaxEta)
            {
               HJetPTVsRawPT.Fill(MJet.JetPT[iJ], MJet.JetRawPT[iJ]);
               HRawPTVsJEC.Fill(MJet.JetRawPT[iJ], MJet.JetPT[iJ] / MJet.JetRawPT[iJ]);
            }

            if(MJet.JetPT[iJ] > 30)
               HJetEtaPhiPT30.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 50)
               HJetEtaPhiPT50.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 70)
               HJetEtaPhiPT70.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 100)
               HJetEtaPhiPT100.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);

            if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               HAllJetPT_EtaN25N15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               HAllJetPT_EtaN15P15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               HAllJetPT_EtaP15P25.Fill(MJet.JetPT[iJ]);
            
            if(BestJetIndex < 0 || MJet.JetPT[iJ] > MJet.JetPT[BestJetIndex])
               BestJetIndex = iJ;
         }

         bool PassL156 = (MHLT.CheckTrigger("L1_SingleJet56_BptxAND") > 0);

         if(BestJetIndex >= 0)
         {
            if(fabs(MJet.JetEta[BestJetIndex]) < 5.2)
               HJetPT.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < 1.5)
               HJetPT_EtaN15P15.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < MaxEta)
               HJetPT_EtaN25P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 0 && MJet.JetEta[BestJetIndex] < MaxEta)
               HJetPT_EtaN00P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < 0)
               HJetPT_EtaN25P00.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 1.5 && MJet.JetEta[BestJetIndex] < MaxEta)
               HJetPT_EtaP15P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < -1.5)
               HJetPT_EtaN25N15.Fill(MJet.JetPT[BestJetIndex]);
            
            if(fabs(MJet.JetEta[BestJetIndex]) < 5.2 && PassL156)
               HJetPTPassL156.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < 1.5 && PassL156)
               HJetPTPassL156_EtaN15P15.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < MaxEta && PassL156)
               HJetPTPassL156_EtaN25P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 0 && MJet.JetEta[BestJetIndex] < MaxEta && PassL156)
               HJetPTPassL156_EtaN00P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < 0 && PassL156)
               HJetPTPassL156_EtaN25P00.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 1.5 && MJet.JetEta[BestJetIndex] < MaxEta && PassL156)
               HJetPTPassL156_EtaP15P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < -1.5 && PassL156)
               HJetPTPassL156_EtaN25N15.Fill(MJet.JetPT[BestJetIndex]);

            if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false)
               HJetEtaPhiPT70FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
            if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false)
               HJetEtaPhiPT80FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
            if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false)
               HJetEtaPhiPT100FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
            if(MJet.JetPT[BestJetIndex] > 120 && PassL156 == false)
               HJetEtaPhiPT120FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
            
            if(MinPTForTrack > 0 && MJet.JetPT[BestJetIndex] > MinPTForTrack)
            {
               bool Matched = false;

               double BestDR2 = -1;
               for(int iJ = 0; iJ < MCaloJet.JetCount; iJ++)
               {
                  if(MCaloJet.JetPT[iJ] < 40)
                     continue;

                  double DEta = MJet.JetEta[BestJetIndex] - MCaloJet.JetEta[iJ];
                  double DPhi = MJet.JetPhi[BestJetIndex] - MCaloJet.JetPhi[iJ];
                  if(DPhi > M_PI)    DPhi = DPhi - 2 * M_PI;
                  if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
                  double DR2 = DEta * DEta + DPhi * DPhi;

                  if(BestDR2 < 0 || BestDR2 > DR2)
                     BestDR2 = DR2;
               }

               if(BestDR2 > 0 && BestDR2 < 0.2 * 0.2)
                  Matched = true;
               
               double BestDR = ((BestDR2 > 0 && BestDR2 < 1) ? sqrt(BestDR2) : 0.999);
               if(PassL156 == true)
                  HCaloPFMatchDR_PassL156.Fill(BestDR);
               else
                  HCaloPFMatchDR_FailL156.Fill(BestDR);

               double AllPT = 0;
               double Algo6PT = 0;
               double AllPTMinPT = 0;
               double Algo6PTMinPT = 0;
               double Algo6PTMVA095 = 0;
               double Algo6PTMVA098 = 0;

               for(int iT = 0; iT < MTrack.TrackCount; iT++)
               {
                  if(MTrack.HighPurity[iT] == false)
                     continue;

                  double DEta = MJet.JetEta[BestJetIndex] - MTrack.TrackEta[iT];
                  double DPhi = MJet.JetPhi[BestJetIndex] - MTrack.TrackPhi[iT];
                  if(DPhi > M_PI)    DPhi = DPhi - 2 * M_PI;
                  if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
                  
                  if(DEta * DEta + DPhi * DPhi > 0.4 * 0.4)
                     continue;

                  AllPT = AllPT + MTrack.TrackPT[iT];
                  if(MTrack.TrackPT[iT] > 0.75)
                     AllPTMinPT = AllPTMinPT + MTrack.TrackPT[iT];
                  if(MTrack.TrackAlgo[iT] == 6)
                     Algo6PT = Algo6PT + MTrack.TrackPT[iT];
                  if(MTrack.TrackAlgo[iT] == 6 && MTrack.TrackPT[iT] > 0.75)
                     Algo6PTMinPT = Algo6PTMinPT + MTrack.TrackPT[iT];
                  if(MTrack.TrackAlgo[iT] == 6 && MTrack.TrackMVA[iT] < 0.95)
                     Algo6PTMVA095 = Algo6PTMVA095 + MTrack.TrackPT[iT];
                  if(MTrack.TrackAlgo[iT] == 6 && MTrack.TrackMVA[iT] < 0.98)
                     Algo6PTMVA098 = Algo6PTMVA098 + MTrack.TrackPT[iT];

                  if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && Matched == true)
                     HTrackAlgo_PT70_Matched.Fill(MTrack.TrackAlgo[iT]);
                  if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && Matched == false)
                     HTrackAlgo_PT70_NonMatch.Fill(MTrack.TrackAlgo[iT]);
                  if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && Matched == true)
                     HTrackAlgo_PT80_Matched.Fill(MTrack.TrackAlgo[iT]);
                  if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && Matched == false)
                     HTrackAlgo_PT80_NonMatch.Fill(MTrack.TrackAlgo[iT]);
                  if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && Matched == true)
                     HTrackAlgo_PT100_Matched.Fill(MTrack.TrackAlgo[iT]);
                  if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && Matched == false)
                     HTrackAlgo_PT100_NonMatch.Fill(MTrack.TrackAlgo[iT]);

  
                  if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && MTrack.TrackAlgo[iT] == 6 && Matched == true)
                  {
                     HTrackPT_Algo6_PT70_Matched.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT70_Matched.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT70_Matched.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT70_Matched.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
                  if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && MTrack.TrackAlgo[iT] == 6 && Matched == false)
                  {
                     HTrackPT_Algo6_PT70_NonMatch.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT70_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT70_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT70_NonMatch.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
                  if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && MTrack.TrackAlgo[iT] == 6 && Matched == true)
                  {
                     HTrackPT_Algo6_PT80_Matched.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT80_Matched.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT80_Matched.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT80_Matched.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
                  if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && MTrack.TrackAlgo[iT] == 6 && Matched == false)
                  {
                     HTrackPT_Algo6_PT80_NonMatch.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT80_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT80_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT80_NonMatch.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
                  if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && MTrack.TrackAlgo[iT] == 6 && Matched == true)
                  {
                     HTrackPT_Algo6_PT100_Matched.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT100_Matched.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT100_Matched.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT100_Matched.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
                  if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && MTrack.TrackAlgo[iT] == 6 && Matched == false)
                  {
                     HTrackPT_Algo6_PT100_NonMatch.Fill(MTrack.TrackPT[iT]);
                     HTrackMVA_Algo6_PT100_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     if(MTrack.TrackPT[iT] > 0.75)
                        HTrackMVA_Algo6MinPT_PT100_NonMatch.Fill(MTrack.TrackMVA[iT]);
                     HTrackPTVsMVA_Algo6_PT100_NonMatch.Fill(MTrack.TrackPT[iT], MTrack.TrackMVA[iT]);
                  }
               }

               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_PT70_Matched.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_PT70_NonMatch.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_PT80_Matched.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_PT80_NonMatch.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_PT100_Matched.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_PT100_NonMatch.Fill(Algo6PT / AllPT);
               
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true)
                  HTrackAlgo6Fraction_PT70_PassL156.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false)
                  HTrackAlgo6Fraction_PT70_FailL156.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true)
                  HTrackAlgo6Fraction_PT80_PassL156.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false)
                  HTrackAlgo6Fraction_PT80_FailL156.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true)
                  HTrackAlgo6Fraction_PT100_PassL156.Fill(Algo6PT / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false)
                  HTrackAlgo6Fraction_PT100_FailL156.Fill(Algo6PT / AllPT);

               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MinPT_PT70_Matched.Fill(Algo6PTMinPT / AllPTMinPT);
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MinPT_PT70_NonMatch.Fill(Algo6PTMinPT / AllPTMinPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MinPT_PT80_Matched.Fill(Algo6PTMinPT / AllPTMinPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MinPT_PT80_NonMatch.Fill(Algo6PTMinPT / AllPTMinPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MinPT_PT100_Matched.Fill(Algo6PTMinPT / AllPTMinPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MinPT_PT100_NonMatch.Fill(Algo6PTMinPT / AllPTMinPT);

               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA095_PT70_Matched.Fill(Algo6PTMVA095 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA095_PT70_NonMatch.Fill(Algo6PTMVA095 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA095_PT80_Matched.Fill(Algo6PTMVA095 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA095_PT80_NonMatch.Fill(Algo6PTMVA095 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA095_PT100_Matched.Fill(Algo6PTMVA095 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA095_PT100_NonMatch.Fill(Algo6PTMVA095 / AllPT);

               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA098_PT70_Matched.Fill(Algo6PTMVA098 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 70 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA098_PT70_NonMatch.Fill(Algo6PTMVA098 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA098_PT80_Matched.Fill(Algo6PTMVA098 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 80 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA098_PT80_NonMatch.Fill(Algo6PTMVA098 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == true && Matched == true)
                  HTrackAlgo6Fraction_MVA098_PT100_Matched.Fill(Algo6PTMVA098 / AllPT);
               if(MJet.JetPT[BestJetIndex] > 100 && PassL156 == false && Matched == false)
                  HTrackAlgo6Fraction_MVA098_PT100_NonMatch.Fill(Algo6PTMVA098 / AllPT);

               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT < 0.2 && PassL156 == true && Matched == true)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT < 0.2 && PassL156 == false && Matched == false)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT < 0.2 && PassL156 == true)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT < 0.2 && PassL156 == false)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT > 0.2 && PassL156 == true && Matched == true)
                  HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT > 0.2 && PassL156 == false && Matched == false)
                  HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT > 0.2 && PassL156 == true)
                  HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT > 0.2 && PassL156 == false)
                  HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               
               if(MJet.JetPT[BestJetIndex] > 50 && Algo6PT / AllPT < 0.25)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT50.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 50 && Algo6PT / AllPT > 0.25)
                  HJetEtaPhi_BadTrackAlgoFraction_PT50.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT < 0.25)
                  HJetEtaPhi_GoodTrackAlgoFraction_PT70.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);
               if(MJet.JetPT[BestJetIndex] > 70 && Algo6PT / AllPT > 0.25)
                  HJetEtaPhi_BadTrackAlgoFraction_PT70.Fill(MJet.JetEta[BestJetIndex], MJet.JetPhi[BestJetIndex]);

               if(PrintDebug == true)
               {
                  if(Algo6PT / AllPT > 0.2 && MJet.JetPT[BestJetIndex] > 80)
                  {
                     cout << endl;
                     cout << "[DEBUG][A6F] " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << endl;
                     cout << "[DEBUG][A6F] Jet " << MJet.JetPT[BestJetIndex] << " " << MJet.JetEta[BestJetIndex]
                        << " " << MJet.JetPhi[BestJetIndex] << endl;
                     cout << "[DEBUG][A6F] Algo6/TrackPT " << Algo6PT << "/" << AllPT << " " << Algo6PT / AllPT << endl;
                     cout << endl;

                     for(int iT = 0; iT < MTrack.TrackCount; iT++)
                     {
                        if(MTrack.HighPurity[iT] == false)
                           continue;

                        double DEta = MJet.JetEta[BestJetIndex] - MTrack.TrackEta[iT];
                        double DPhi = MJet.JetPhi[BestJetIndex] - MTrack.TrackPhi[iT];
                        if(DPhi > M_PI)    DPhi = DPhi - 2 * M_PI;
                        if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;

                        if(DEta * DEta + DPhi * DPhi > 0.4 * 0.4)
                           continue;

                        cout << "[DEBUG][A6F] T[" << (int)MTrack.TrackAlgo[iT] << "] " << MTrack.TrackPT[iT] << " " << MTrack.TrackEta[iT] << " " << MTrack.TrackPhi[iT] << " " << MTrack.TrackMVA[iT] << endl;
                     }
                  }
               }
            }
 
            if(PrintDebug == true)
            {
               if(fabs(MJet.JetEta[BestJetIndex]) < 1.5 && PassL156 == false && MJet.JetPT[BestJetIndex] > 100)
               {
                  cout << endl;
                  cout << "[DEBUG] " << MHiEvent.Run << " " << MHiEvent.Lumi << " " << MHiEvent.Event << endl;
                  cout << "[DEBUG] Jet " << MJet.JetPT[BestJetIndex] << " " << MJet.JetEta[BestJetIndex]
                     << " " << MJet.JetPhi[BestJetIndex] << endl;
               }
            }
         }

         // PF plots
         if(MPF.Tree != NULL)
         {
            for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
            {
               if((*MPF.Eta)[iPF] > -2.5 && (*MPF.Eta)[iPF] < -1.5)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFPT_ID1_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFPT_ID2_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFPT_ID3_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFPT_ID4_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFPT_ID5_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFPT_ID6_EtaN25N15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFPT_ID7_EtaN25N15.Fill((*MPF.PT)[iPF]);
               }
               if((*MPF.Eta)[iPF] > -1.5 && (*MPF.Eta)[iPF] < 1.5)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFPT_ID1_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFPT_ID2_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFPT_ID3_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFPT_ID4_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFPT_ID5_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFPT_ID6_EtaN15P15.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFPT_ID7_EtaN15P15.Fill((*MPF.PT)[iPF]);
               }
               if((*MPF.Eta)[iPF] > 1.5 && (*MPF.Eta)[iPF] < 2.5)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFPT_ID1_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFPT_ID2_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFPT_ID3_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFPT_ID4_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFPT_ID5_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFPT_ID6_EtaP15P25.Fill((*MPF.PT)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFPT_ID7_EtaP15P25.Fill((*MPF.PT)[iPF]);
               }

               if((*MPF.PT)[iPF] > 0.5)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 1.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 2.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 5.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 10.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 20.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 50.0)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_ID1_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_ID2_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_ID3_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_ID4_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_ID5_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_ID6_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_ID7_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               
               if((*MPF.PT)[iPF] > 0.5 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT05.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 1.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT10.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 2.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT20.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 5.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT50.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 10.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT100.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 20.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT200.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
               if((*MPF.PT)[iPF] > 50.0 && MHiEvent.hiBin >= 100)
               {
                  if((*MPF.ID)[iPF] == 1)   HPFEtaPhi_Peripheral_ID1_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 2)   HPFEtaPhi_Peripheral_ID2_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 3)   HPFEtaPhi_Peripheral_ID3_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 4)   HPFEtaPhi_Peripheral_ID4_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 5)   HPFEtaPhi_Peripheral_ID5_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 6)   HPFEtaPhi_Peripheral_ID6_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
                  if((*MPF.ID)[iPF] == 7)   HPFEtaPhi_Peripheral_ID7_PT500.Fill((*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
               }
            }
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();

   vector<string> Explanation(15);
   Explanation[0] = "Selections";
   Explanation[1] = "";
   Explanation[2] = "Other than fraction plots, all jets have";
   Explanation[3] = "   * CHF > 0.01";
   Explanation[4] = "   * NHF > 0.01";
   Explanation[5] = "   * MUF < 0.01";
   Explanation[6] = "";
   Explanation[7] = "Good lumi selected based on JSON";
   Explanation[8] = "";
   Explanation[9] = "";
   if(ReducedEta == true)
      Explanation[9] = "Reject jets between |eta| = 2.2 - 2.5";
   PdfFile.AddTextPage(Explanation);

   HJetEtaPhiPT30.SetStats(0);
   HJetEtaPhiPT50.SetStats(0);
   HJetEtaPhiPT70.SetStats(0);
   HJetEtaPhiPT100.SetStats(0);

   PdfFile.AddPlot(HJetEtaPhiPT30, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT50, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT70, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT100, "colz");

   HJetPT.SetStats(0);
   HJetPTPassL156.SetLineColor(kRed);
   HJetPT_EtaN15P15.SetStats(0);
   HJetPTPassL156_EtaN15P15.SetLineColor(kRed);
   HJetPT_EtaN25P25.SetStats(0);
   HJetPTPassL156_EtaN25P25.SetLineColor(kRed);
   HJetPT_EtaN00P25.SetStats(0);
   HJetPTPassL156_EtaN00P25.SetLineColor(kRed);
   HJetPT_EtaN25P00.SetStats(0);
   HJetPTPassL156_EtaN25P00.SetLineColor(kRed);
   HJetPT_EtaP15P25.SetStats(0);
   HJetPTPassL156_EtaP15P25.SetLineColor(kRed);
   HJetPT_EtaN25N15.SetStats(0);
   HJetPTPassL156_EtaN25N15.SetLineColor(kRed);

   TCanvas Canvas;
   TGraphAsymmErrors GTurnOn;
   TGraphAsymmErrors GTurnOn_EtaN15P15;
   TGraphAsymmErrors GTurnOn_EtaN25P25;
   TGraphAsymmErrors GTurnOn_EtaN00P25;
   TGraphAsymmErrors GTurnOn_EtaN25P00;
   TGraphAsymmErrors GTurnOn_EtaP15P25;
   TGraphAsymmErrors GTurnOn_EtaN25N15;
   
   GTurnOn.Divide(&HJetPTPassL156, &HJetPT);
   GTurnOn_EtaN15P15.Divide(&HJetPTPassL156_EtaN15P15, &HJetPT_EtaN15P15);
   GTurnOn_EtaN25P25.Divide(&HJetPTPassL156_EtaN25P25, &HJetPT_EtaN25P25);
   GTurnOn_EtaN00P25.Divide(&HJetPTPassL156_EtaN00P25, &HJetPT_EtaN00P25);
   GTurnOn_EtaN25P00.Divide(&HJetPTPassL156_EtaN25P00, &HJetPT_EtaN25P00);
   GTurnOn_EtaP15P25.Divide(&HJetPTPassL156_EtaP15P25, &HJetPT_EtaP15P25);
   GTurnOn_EtaN25N15.Divide(&HJetPTPassL156_EtaN25N15, &HJetPT_EtaN25N15);

   TF1 FTurnOn("FTurnOn", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN15P15("FTurnOn_EtaN15P15", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25P25("FTurnOn_EtaN25P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN00P25("FTurnOn_EtaN00P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25P00("FTurnOn_EtaN25P00", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaP15P25("FTurnOn_EtaP15P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25N15("FTurnOn_EtaN25N15", Function.c_str(), 0, 200);

   FTurnOn.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN15P15.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN00P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25P00.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaP15P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25N15.SetParameters(0.05, 30, 7, 1.0, 0.0);
   
   FTurnOn.FixParameter(3, 1.0);
   FTurnOn_EtaN15P15.FixParameter(3, 1.0);
   FTurnOn_EtaN25P25.FixParameter(3, 1.0);
   FTurnOn_EtaN00P25.FixParameter(3, 1.0);
   FTurnOn_EtaN25P00.FixParameter(3, 1.0);
   FTurnOn_EtaP15P25.FixParameter(3, 1.0);
   FTurnOn_EtaN25N15.FixParameter(3, 1.0);
   
   FTurnOn.FixParameter(4, 0.0);
   FTurnOn_EtaN15P15.FixParameter(4, 0.0);
   FTurnOn_EtaN25P25.FixParameter(4, 0.0);
   FTurnOn_EtaN00P25.FixParameter(4, 0.0);
   FTurnOn_EtaN25P00.FixParameter(4, 0.0);
   FTurnOn_EtaP15P25.FixParameter(4, 0.0);
   FTurnOn_EtaN25N15.FixParameter(4, 0.0);
   
   FTurnOn.SetTitle("");
   FTurnOn_EtaN15P15.SetTitle("");
   FTurnOn_EtaN25P25.SetTitle("");
   FTurnOn_EtaN00P25.SetTitle("");
   FTurnOn_EtaN25P00.SetTitle("");
   FTurnOn_EtaP15P25.SetTitle("");
   FTurnOn_EtaN25N15.SetTitle("");
   
   FTurnOn.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN15P15.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN00P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25P00.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaP15P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25N15.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   
   GTurnOn.Fit(&FTurnOn, "0");
   GTurnOn_EtaN15P15.Fit(&FTurnOn_EtaN15P15, "0");
   GTurnOn_EtaN25P25.Fit(&FTurnOn_EtaN25P25, "0");
   GTurnOn_EtaN00P25.Fit(&FTurnOn_EtaN00P25, "0");
   GTurnOn_EtaN25P00.Fit(&FTurnOn_EtaN25P00, "0");
   GTurnOn_EtaP15P25.Fit(&FTurnOn_EtaP15P25, "0");
   GTurnOn_EtaN25N15.Fit(&FTurnOn_EtaN25N15, "0");

   TH2D HWorldFit("HWorldFit", ";p_{T};Efficiency", 100, 0, 200, 100, 0, 1.1);
   HWorldFit.SetStats(0);
   
   HJetPT.Draw();
   HJetPTPassL156.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn.Draw("same");
   GTurnOn.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);
   
   HJetPT_EtaN15P15.Draw();
   HJetPTPassL156_EtaN15P15.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN15P15.Draw("same");
   GTurnOn_EtaN15P15.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25P25.Draw();
   HJetPTPassL156_EtaN25P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25P25.Draw("same");
   GTurnOn_EtaN25P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN00P25.Draw();
   HJetPTPassL156_EtaN00P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN00P25.Draw("same");
   GTurnOn_EtaN00P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25P00.Draw();
   HJetPTPassL156_EtaN25P00.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25P00.Draw("same");
   GTurnOn_EtaN25P00.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaP15P25.Draw();
   HJetPTPassL156_EtaP15P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaP15P25.Draw("same");
   GTurnOn_EtaP15P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25N15.Draw();
   HJetPTPassL156_EtaN25N15.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25N15.Draw("same");
   GTurnOn_EtaN25N15.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   if(GTurnOn.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   if(GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   if(GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats") != nullptr)
      ((TPaveStats *)GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);

   GTurnOn_EtaN25P00.SetLineColor(kRed);
   GTurnOn_EtaN25P00.SetMarkerColor(kRed);
   GTurnOn_EtaN00P25.Draw("ap");
   GTurnOn_EtaN25P00.Draw("p");
   TLegend Legend1(0.5, 0.2, 0.8, 0.4);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&GTurnOn_EtaN00P25, "0 < #eta < 2.5", "pl");
   Legend1.AddEntry(&GTurnOn_EtaN25P00, "-2.5 < #eta < 0", "pl");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   GTurnOn_EtaN25N15.SetLineColor(kBlack);
   GTurnOn_EtaN25N15.SetMarkerColor(kBlack);
   GTurnOn_EtaN15P15.SetLineColor(kGreen);
   GTurnOn_EtaN15P15.SetMarkerColor(kGreen);
   GTurnOn_EtaP15P25.SetLineColor(kRed);
   GTurnOn_EtaP15P25.SetMarkerColor(kRed);
   GTurnOn_EtaN15P15.Draw("ap");
   GTurnOn_EtaP15P25.Draw("p");
   GTurnOn_EtaN25N15.Draw("p");
   TLegend Legend2(0.5, 0.2, 0.8, 0.4);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&GTurnOn_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   Legend2.AddEntry(&GTurnOn_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   Legend2.AddEntry(&GTurnOn_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HJetEtaPhiPT70FailL156.SetStats(0);
   HJetEtaPhiPT80FailL156.SetStats(0);
   HJetEtaPhiPT100FailL156.SetStats(0);
   HJetEtaPhiPT120FailL156.SetStats(0);

   PdfFile.AddPlot(HJetEtaPhiPT70FailL156, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT80FailL156, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT100FailL156, "colz");
   PdfFile.AddPlot(HJetEtaPhiPT120FailL156, "colz");

   HJetPTVsRawPT.SetStats(0);
   HRawPTVsJEC.SetStats(0);
   PdfFile.AddPlot(HJetPTVsRawPT, "colz");
   PdfFile.AddPlot(HRawPTVsJEC, "colz");

   HAllJetPT_EtaN25N15.SetStats(0);
   HAllJetPT_EtaN15P15.SetStats(0);
   HAllJetPT_EtaP15P25.SetStats(0);

   HAllJetPT_EtaN25N15.SetLineColor(kBlack);
   HAllJetPT_EtaN15P15.SetLineColor(kGreen);
   HAllJetPT_EtaP15P25.SetLineColor(kRed);
   
   HAllJetPT_EtaN25N15.SetMarkerColor(kBlack);
   HAllJetPT_EtaN15P15.SetMarkerColor(kGreen);
   HAllJetPT_EtaP15P25.SetMarkerColor(kRed);

   TH2D HWorldPT("HWorldPT", ";PT;", 100, 0, 200, 100, 1e-7, 1.0);
   HWorldPT.SetStats(0);
   HWorldPT.Draw("axis");
   HAllJetPT_EtaN25N15.DrawNormalized("same");
   HAllJetPT_EtaN15P15.DrawNormalized("same");
   HAllJetPT_EtaP15P25.DrawNormalized("same");
   TLegend LegendPT(0.4, 0.6, 0.7, 0.8);
   LegendPT.SetTextFont(42);
   LegendPT.SetTextSize(0.035);
   LegendPT.SetBorderSize(0);
   LegendPT.SetFillStyle(0);
   LegendPT.AddEntry(&HAllJetPT_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendPT.AddEntry(&HAllJetPT_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendPT.AddEntry(&HAllJetPT_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendPT.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HJetCHF_PT50_EtaN25N15.SetStats(0);
   HJetCHF_PT50_EtaN15P15.SetStats(0);
   HJetCHF_PT50_EtaP15P25.SetStats(0);
   HJetCEF_PT50_EtaN25N15.SetStats(0);
   HJetCEF_PT50_EtaN15P15.SetStats(0);
   HJetCEF_PT50_EtaP15P25.SetStats(0);
   HJetNHF_PT50_EtaN25N15.SetStats(0);
   HJetNHF_PT50_EtaN15P15.SetStats(0);
   HJetNHF_PT50_EtaP15P25.SetStats(0);
   HJetNEF_PT50_EtaN25N15.SetStats(0);
   HJetNEF_PT50_EtaN15P15.SetStats(0);
   HJetNEF_PT50_EtaP15P25.SetStats(0);
   HJetMUF_PT50_EtaN25N15.SetStats(0);
   HJetMUF_PT50_EtaN15P15.SetStats(0);
   HJetMUF_PT50_EtaP15P25.SetStats(0);
   HJetCH_PT50_EtaN25N15.SetStats(0);
   HJetCH_PT50_EtaN15P15.SetStats(0);
   HJetCH_PT50_EtaP15P25.SetStats(0);
   HJetCE_PT50_EtaN25N15.SetStats(0);
   HJetCE_PT50_EtaN15P15.SetStats(0);
   HJetCE_PT50_EtaP15P25.SetStats(0);
   HJetNH_PT50_EtaN25N15.SetStats(0);
   HJetNH_PT50_EtaN15P15.SetStats(0);
   HJetNH_PT50_EtaP15P25.SetStats(0);
   HJetNE_PT50_EtaN25N15.SetStats(0);
   HJetNE_PT50_EtaN15P15.SetStats(0);
   HJetNE_PT50_EtaP15P25.SetStats(0);
   HJetMU_PT50_EtaN25N15.SetStats(0);
   HJetMU_PT50_EtaN15P15.SetStats(0);
   HJetMU_PT50_EtaP15P25.SetStats(0);
   HJetHad_PT50_EtaN25N15.SetStats(0);
   HJetHad_PT50_EtaN15P15.SetStats(0);
   HJetHad_PT50_EtaP15P25.SetStats(0);
   HJetCHF_PT70_EtaN25N15.SetStats(0);
   HJetCHF_PT70_EtaN15P15.SetStats(0);
   HJetCHF_PT70_EtaP15P25.SetStats(0);
   HJetCEF_PT70_EtaN25N15.SetStats(0);
   HJetCEF_PT70_EtaN15P15.SetStats(0);
   HJetCEF_PT70_EtaP15P25.SetStats(0);
   HJetNHF_PT70_EtaN25N15.SetStats(0);
   HJetNHF_PT70_EtaN15P15.SetStats(0);
   HJetNHF_PT70_EtaP15P25.SetStats(0);
   HJetNEF_PT70_EtaN25N15.SetStats(0);
   HJetNEF_PT70_EtaN15P15.SetStats(0);
   HJetNEF_PT70_EtaP15P25.SetStats(0);
   HJetMUF_PT70_EtaN25N15.SetStats(0);
   HJetMUF_PT70_EtaN15P15.SetStats(0);
   HJetMUF_PT70_EtaP15P25.SetStats(0);
   HJetCH_PT70_EtaN25N15.SetStats(0);
   HJetCH_PT70_EtaN15P15.SetStats(0);
   HJetCH_PT70_EtaP15P25.SetStats(0);
   HJetCE_PT70_EtaN25N15.SetStats(0);
   HJetCE_PT70_EtaN15P15.SetStats(0);
   HJetCE_PT70_EtaP15P25.SetStats(0);
   HJetNH_PT70_EtaN25N15.SetStats(0);
   HJetNH_PT70_EtaN15P15.SetStats(0);
   HJetNH_PT70_EtaP15P25.SetStats(0);
   HJetNE_PT70_EtaN25N15.SetStats(0);
   HJetNE_PT70_EtaN15P15.SetStats(0);
   HJetNE_PT70_EtaP15P25.SetStats(0);
   HJetMU_PT70_EtaN25N15.SetStats(0);
   HJetMU_PT70_EtaN15P15.SetStats(0);
   HJetMU_PT70_EtaP15P25.SetStats(0);
   HJetHad_PT70_EtaN25N15.SetStats(0);
   HJetHad_PT70_EtaN15P15.SetStats(0);
   HJetHad_PT70_EtaP15P25.SetStats(0);

   HJetCHF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCHF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCHF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCEF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCEF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCEF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNHF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNHF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNHF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNEF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNEF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNEF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetMUF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetMUF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetMUF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCH_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCH_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCH_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCE_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCE_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCE_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNH_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNH_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNH_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNE_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNE_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNE_PT50_EtaP15P25.SetLineColor(kRed);
   HJetMU_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetMU_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetMU_PT50_EtaP15P25.SetLineColor(kRed);
   HJetHad_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetHad_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetHad_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCHF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCHF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCHF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCEF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCEF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCEF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNHF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNHF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNHF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNEF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNEF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNEF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetMUF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetMUF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetMUF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCH_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCH_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCH_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCE_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCE_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCE_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNH_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNH_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNH_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNE_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNE_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNE_PT70_EtaP15P25.SetLineColor(kRed);
   HJetMU_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetMU_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetMU_PT70_EtaP15P25.SetLineColor(kRed);
   HJetHad_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetHad_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetHad_PT70_EtaP15P25.SetLineColor(kRed);
   
   HJetCHF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCHF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCHF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCEF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCEF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCEF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNHF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNHF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNHF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNEF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNEF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNEF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetMUF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetMUF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetMUF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCH_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCH_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCH_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCE_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCE_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCE_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNH_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNH_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNH_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNE_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNE_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNE_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetMU_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetMU_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetMU_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetHad_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetHad_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetHad_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCHF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCHF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCHF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCEF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCEF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCEF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNHF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNHF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNHF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNEF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNEF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNEF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetMUF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetMUF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetMUF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCH_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCH_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCH_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCE_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCE_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCE_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNH_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNH_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNH_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNE_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNE_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNE_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetMU_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetMU_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetMU_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetHad_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetHad_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetHad_PT70_EtaP15P25.SetMarkerColor(kRed);

   TH2D HWorldCHF("HWorldCHF", "p_{T} > 50 GeV;CHF;", 100, 0, 1, 100, 0, 0.1);
   HWorldCHF.SetStats(0);
   HWorldCHF.Draw("axis");
   HJetCHF_PT50_EtaN25N15.DrawNormalized("same");
   HJetCHF_PT50_EtaN15P15.DrawNormalized("same");
   HJetCHF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendCHF(0.4, 0.6, 0.7, 0.8);
   LegendCHF.SetTextFont(42);
   LegendCHF.SetTextSize(0.035);
   LegendCHF.SetBorderSize(0);
   LegendCHF.SetFillStyle(0);
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendCHF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldCHF.Draw("axis");
   HWorldCHF.SetTitle("p_{T} > 70 GeV");
   HJetCHF_PT70_EtaN25N15.DrawNormalized("same");
   HJetCHF_PT70_EtaN15P15.DrawNormalized("same");
   HJetCHF_PT70_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCH("HWorldCH", "p_{T} > 50 GeV;CH Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldCH.SetStats(0);
   HWorldCH.Draw("axis");
   HJetCH_PT50_EtaN25N15.DrawNormalized("same");
   HJetCH_PT50_EtaN15P15.DrawNormalized("same");
   HJetCH_PT50_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldCH.Draw("axis");
   HWorldCH.SetTitle("p_{T} > 70 GeV");
   HJetCH_PT70_EtaN25N15.DrawNormalized("same");
   HJetCH_PT70_EtaN15P15.DrawNormalized("same");
   HJetCH_PT70_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCEF("HWorldCEF", "p_{T} > 50 GeV;CEF;", 100, 0, 1, 100, 0, 0.1);
   HWorldCEF.SetStats(0);
   HWorldCEF.Draw("axis");
   HJetCEF_PT50_EtaN25N15.DrawNormalized("same");
   HJetCEF_PT50_EtaN15P15.DrawNormalized("same");
   HJetCEF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendCEF(0.4, 0.6, 0.7, 0.8);
   LegendCEF.SetTextFont(42);
   LegendCEF.SetTextSize(0.035);
   LegendCEF.SetBorderSize(0);
   LegendCEF.SetFillStyle(0);
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendCEF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldCEF.Draw("axis");
   HWorldCEF.SetTitle("p_{T} > 70 GeV");
   HJetCEF_PT70_EtaN25N15.DrawNormalized("same");
   HJetCEF_PT70_EtaN15P15.DrawNormalized("same");
   HJetCEF_PT70_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCE("HWorldCE", "p_{T} > 50 GeV;CE Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldCE.SetStats(0);
   HWorldCE.Draw("axis");
   HJetCE_PT50_EtaN25N15.DrawNormalized("same");
   HJetCE_PT50_EtaN15P15.DrawNormalized("same");
   HJetCE_PT50_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldCE.Draw("axis");
   HWorldCE.SetTitle("p_{T} > 70 GeV");
   HJetCE_PT70_EtaN25N15.DrawNormalized("same");
   HJetCE_PT70_EtaN15P15.DrawNormalized("same");
   HJetCE_PT70_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNHF("HWorldNHF", "p_{T} > 50 GeV;NHF;", 100, 0, 1, 100, 0, 0.1);
   HWorldNHF.SetStats(0);
   HWorldNHF.Draw("axis");
   HJetNHF_PT50_EtaN25N15.DrawNormalized("same");
   HJetNHF_PT50_EtaN15P15.DrawNormalized("same");
   HJetNHF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendNHF(0.4, 0.6, 0.7, 0.8);
   LegendNHF.SetTextFont(42);
   LegendNHF.SetTextSize(0.035);
   LegendNHF.SetBorderSize(0);
   LegendNHF.SetFillStyle(0);
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendNHF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldNHF.Draw("axis");
   HWorldNHF.SetTitle("p_{T} > 70 GeV");
   HJetNHF_PT70_EtaN25N15.DrawNormalized("same");
   HJetNHF_PT70_EtaN15P15.DrawNormalized("same");
   HJetNHF_PT70_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNH("HWorldNH", "p_{T} > 50 GeV;NH Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldNH.SetStats(0);
   HWorldNH.Draw("axis");
   HJetNH_PT50_EtaN25N15.DrawNormalized("same");
   HJetNH_PT50_EtaN15P15.DrawNormalized("same");
   HJetNH_PT50_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldNH.Draw("axis");
   HWorldNH.SetTitle("p_{T} > 70 GeV");
   HJetNH_PT70_EtaN25N15.DrawNormalized("same");
   HJetNH_PT70_EtaN15P15.DrawNormalized("same");
   HJetNH_PT70_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   TH2D HWorldNEF("HWorldNEF", "p_{T} > 50 GeV;NEF;", 100, 0, 1, 100, 0, 0.1);
   HWorldNEF.SetStats(0);
   HWorldNEF.Draw("axis");
   HJetNEF_PT50_EtaN25N15.DrawNormalized("same");
   HJetNEF_PT50_EtaN15P15.DrawNormalized("same");
   HJetNEF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendNEF(0.4, 0.6, 0.7, 0.8);
   LegendNEF.SetTextFont(42);
   LegendNEF.SetTextSize(0.035);
   LegendNEF.SetBorderSize(0);
   LegendNEF.SetFillStyle(0);
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendNEF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldNEF.Draw("axis");
   HWorldNEF.SetTitle("p_{T} > 70 GeV");
   HJetNEF_PT70_EtaN25N15.DrawNormalized("same");
   HJetNEF_PT70_EtaN15P15.DrawNormalized("same");
   HJetNEF_PT70_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNE("HWorldNE", "p_{T} > 50 GeV;NE Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldNE.SetStats(0);
   HWorldNE.Draw("axis");
   HJetNE_PT50_EtaN25N15.DrawNormalized("same");
   HJetNE_PT50_EtaN15P15.DrawNormalized("same");
   HJetNE_PT50_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldNE.Draw("axis");
   HWorldNE.SetTitle("p_{T} > 70 GeV");
   HJetNE_PT70_EtaN25N15.DrawNormalized("same");
   HJetNE_PT70_EtaN15P15.DrawNormalized("same");
   HJetNE_PT70_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldMUF("HWorldMUF", "p_{T} > 50 GeV;MUF;", 100, 0, 1, 100, 0, 0.1);
   HWorldMUF.SetStats(0);
   HWorldMUF.Draw("axis");
   HJetMUF_PT50_EtaN25N15.DrawNormalized("same");
   HJetMUF_PT50_EtaN15P15.DrawNormalized("same");
   HJetMUF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendMUF(0.4, 0.6, 0.7, 0.8);
   LegendMUF.SetTextFont(42);
   LegendMUF.SetTextSize(0.035);
   LegendMUF.SetBorderSize(0);
   LegendMUF.SetFillStyle(0);
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendMUF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldMUF.Draw("axis");
   HWorldMUF.SetTitle("p_{T} > 70 GeV");
   HJetMUF_PT70_EtaN25N15.DrawNormalized("same");
   HJetMUF_PT70_EtaN15P15.DrawNormalized("same");
   HJetMUF_PT70_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldMU("HWorldMU", "p_{T} > 50 GeV;MU Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldMU.SetStats(0);
   HWorldMU.Draw("axis");
   HJetMU_PT50_EtaN25N15.DrawNormalized("same");
   HJetMU_PT50_EtaN15P15.DrawNormalized("same");
   HJetMU_PT50_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldMU.Draw("axis");
   HWorldMU.SetTitle("p_{T} > 70 GeV");
   HJetMU_PT70_EtaN25N15.DrawNormalized("same");
   HJetMU_PT70_EtaN15P15.DrawNormalized("same");
   HJetMU_PT70_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldHad("HWorldHad", "p_{T} > 50 GeV;Had Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldHad.SetStats(0);
   HWorldHad.Draw("axis");
   HJetHad_PT50_EtaN25N15.DrawNormalized("same");
   HJetHad_PT50_EtaN15P15.DrawNormalized("same");
   HJetHad_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendHad(0.4, 0.6, 0.7, 0.8);
   LegendHad.SetTextFont(42);
   LegendHad.SetTextSize(0.035);
   LegendHad.SetBorderSize(0);
   LegendHad.SetFillStyle(0);
   LegendHad.AddEntry(&HJetHad_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendHad.AddEntry(&HJetHad_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendHad.AddEntry(&HJetHad_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendHad.Draw();
   LegendHad.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldHad.Draw("axis");
   HWorldHad.SetTitle("p_{T} > 70 GeV");
   HJetHad_PT70_EtaN25N15.DrawNormalized("same");
   HJetHad_PT70_EtaN15P15.DrawNormalized("same");
   HJetHad_PT70_EtaP15P25.DrawNormalized("same");
   LegendHad.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   HCaloPFMatchDR_PassL156.SetStats(0);
   HCaloPFMatchDR_FailL156.SetStats(0);
   
   HCaloPFMatchDR_PassL156.SetLineColor(kBlack);
   HCaloPFMatchDR_FailL156.SetLineColor(kRed);
   
   TH2D HWorldDR("HWorldDR", ";#DeltaR;", 100, 0, 1, 100, 1e-5, 1);
   HWorldDR.SetStats(0);
   HWorldDR.Draw("axis");
   HWorldDR.SetTitle("Matching between Calo and PF");
   HCaloPFMatchDR_PassL156.DrawNormalized("same");
   HCaloPFMatchDR_FailL156.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Pass L1} #color[2]{Fail L1}");
   PdfFile.AddCanvas(Canvas);
 
   HTrackAlgo_PT70_Matched.SetStats(0);
   HTrackAlgo_PT70_NonMatch.SetStats(0);
   HTrackPT_Algo6_PT70_Matched.SetStats(0);
   HTrackPT_Algo6_PT70_NonMatch.SetStats(0);
   HTrackMVA_Algo6_PT70_Matched.SetStats(0);
   HTrackMVA_Algo6_PT70_NonMatch.SetStats(0);
   HTrackMVA_Algo6MinPT_PT70_Matched.SetStats(0);
   HTrackMVA_Algo6MinPT_PT70_NonMatch.SetStats(0);
   HTrackPTVsMVA_Algo6_PT70_Matched.SetStats(0);
   HTrackPTVsMVA_Algo6_PT70_NonMatch.SetStats(0);
   HTrackAlgo_PT80_Matched.SetStats(0);
   HTrackAlgo_PT80_NonMatch.SetStats(0);
   HTrackPT_Algo6_PT80_Matched.SetStats(0);
   HTrackPT_Algo6_PT80_NonMatch.SetStats(0);
   HTrackMVA_Algo6_PT80_Matched.SetStats(0);
   HTrackMVA_Algo6_PT80_NonMatch.SetStats(0);
   HTrackMVA_Algo6MinPT_PT80_Matched.SetStats(0);
   HTrackMVA_Algo6MinPT_PT80_NonMatch.SetStats(0);
   HTrackPTVsMVA_Algo6_PT80_Matched.SetStats(0);
   HTrackPTVsMVA_Algo6_PT80_NonMatch.SetStats(0);
   HTrackAlgo_PT100_Matched.SetStats(0);
   HTrackAlgo_PT100_NonMatch.SetStats(0);
   HTrackPT_Algo6_PT100_Matched.SetStats(0);
   HTrackPT_Algo6_PT100_NonMatch.SetStats(0);
   HTrackMVA_Algo6_PT100_Matched.SetStats(0);
   HTrackMVA_Algo6_PT100_NonMatch.SetStats(0);
   HTrackMVA_Algo6MinPT_PT100_Matched.SetStats(0);
   HTrackMVA_Algo6MinPT_PT100_NonMatch.SetStats(0);
   HTrackPTVsMVA_Algo6_PT100_Matched.SetStats(0);
   HTrackPTVsMVA_Algo6_PT100_NonMatch.SetStats(0);

   PdfFile.AddPlot(HTrackAlgo_PT70_Matched, "hist text00");
   PdfFile.AddPlot(HTrackAlgo_PT70_NonMatch, "hist text00");

   HTrackPT_Algo6_PT70_NonMatch.SetLineColor(kRed);

   TH2D HWorldTrackPT("HWorldTrackPT", ";Track p_{T};", 100, 0, 25, 100, 1e-5, 1);
   HWorldTrackPT.SetStats(0);
   HWorldTrackPT.Draw("axis");
   HWorldTrackPT.SetTitle("Algo 6, jet PT > 70");
   HTrackPT_Algo6_PT70_Matched.DrawNormalized("same");
   HTrackPT_Algo6_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   
   HTrackMVA_Algo6_PT70_NonMatch.SetLineColor(kRed);
   HTrackMVA_Algo6MinPT_PT70_NonMatch.SetLineColor(kRed);

   TH2D HWorldTrackMVA("HWorldTrackMVA", ";Track MVA;", 100, 0.88, 1.02, 100, 0, 0.1);
   HWorldTrackMVA.SetStats(0);
   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 70");
   HTrackMVA_Algo6_PT70_Matched.DrawNormalized("same");
   HTrackMVA_Algo6_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 70, track PT > 750 MeV");
   HTrackMVA_Algo6MinPT_PT70_Matched.DrawNormalized("same");
   HTrackMVA_Algo6MinPT_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT70_Matched, "colz");
   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT70_NonMatch, "colz");

   PdfFile.AddPlot(HTrackAlgo_PT80_Matched, "hist text00");
   PdfFile.AddPlot(HTrackAlgo_PT80_NonMatch, "hist text00");

   HTrackPT_Algo6_PT80_NonMatch.SetLineColor(kRed);

   HWorldTrackPT.Draw("axis");
   HWorldTrackPT.SetTitle("Algo 6, jet PT > 80");
   HTrackPT_Algo6_PT80_Matched.DrawNormalized("same");
   HTrackPT_Algo6_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   
   HTrackMVA_Algo6_PT80_NonMatch.SetLineColor(kRed);
   HTrackMVA_Algo6MinPT_PT80_NonMatch.SetLineColor(kRed);

   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 80");
   HTrackMVA_Algo6_PT80_Matched.DrawNormalized("same");
   HTrackMVA_Algo6_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 80, track PT > 750 MeV");
   HTrackMVA_Algo6MinPT_PT80_Matched.DrawNormalized("same");
   HTrackMVA_Algo6MinPT_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT80_Matched, "colz");
   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT80_NonMatch, "colz");

   PdfFile.AddPlot(HTrackAlgo_PT100_Matched, "hist text00");
   PdfFile.AddPlot(HTrackAlgo_PT100_NonMatch, "hist text00");

   HTrackPT_Algo6_PT100_NonMatch.SetLineColor(kRed);

   HWorldTrackPT.Draw("axis");
   HWorldTrackPT.SetTitle("Algo 6, jet PT > 100");
   HTrackPT_Algo6_PT100_Matched.DrawNormalized("same");
   HTrackPT_Algo6_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   
   HTrackMVA_Algo6_PT100_NonMatch.SetLineColor(kRed);
   HTrackMVA_Algo6MinPT_PT100_NonMatch.SetLineColor(kRed);

   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 100");
   HTrackMVA_Algo6_PT100_Matched.DrawNormalized("same");
   HTrackMVA_Algo6_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   HWorldTrackMVA.Draw("axis");
   HWorldTrackMVA.SetTitle("Algo 6, jet PT > 100, track PT > 750 MeV");
   HTrackMVA_Algo6MinPT_PT100_Matched.DrawNormalized("same");
   HTrackMVA_Algo6MinPT_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT100_Matched, "colz");
   PdfFile.AddPlot(HTrackPTVsMVA_Algo6_PT100_NonMatch, "colz");

   TH2D HWorldAlgo6Fraction("HWorldAlgo6Fraction", ";Sum(Algo 6) / Sum(Track);", 100, 0, 1, 100, 1e-5, 1);
   HWorldAlgo6Fraction.SetStats(0);

   HTrackAlgo6Fraction_PT70_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 70");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT70_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_PT80_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 80");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT80_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_PT100_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 100");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT100_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_PT70_FailL156.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 70");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT70_PassL156.DrawNormalized("same");
   HTrackAlgo6Fraction_PT70_FailL156.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Pass} #color[2]{Fail}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_PT80_FailL156.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 80");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT80_PassL156.DrawNormalized("same");
   HTrackAlgo6Fraction_PT80_FailL156.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Pass} #color[2]{Fail}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_PT100_FailL156.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 100");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_PT100_PassL156.DrawNormalized("same");
   HTrackAlgo6Fraction_PT100_FailL156.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Pass} #color[2]{Fail}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MinPT_PT70_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 70, track PT > 750 MeV");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MinPT_PT70_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MinPT_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MinPT_PT80_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 80, track PT > 750 MeV");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MinPT_PT80_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MinPT_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MinPT_PT100_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 100, track PT > 750 MeV");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MinPT_PT100_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MinPT_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA095_PT70_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 70");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.95) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA095_PT70_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA095_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA095_PT80_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 80");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.95) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA095_PT80_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA095_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA095_PT100_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 100");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.95) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA095_PT100_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA095_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA098_PT70_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 70");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.98) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA098_PT70_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA098_PT70_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA098_PT80_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 80");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.98) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA098_PT80_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA098_PT80_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HTrackAlgo6Fraction_MVA098_PT100_NonMatch.SetLineColor(kRed);
   HWorldAlgo6Fraction.SetTitle("Jet PT > 100");
   HWorldAlgo6Fraction.GetXaxis()->SetTitle("Sum(Algo6 with MVA < 0.98) / Sum(Track)");
   HWorldAlgo6Fraction.Draw("axis");
   HTrackAlgo6Fraction_MVA098_PT100_Matched.DrawNormalized("same");
   HTrackAlgo6Fraction_MVA098_PT100_NonMatch.DrawNormalized("same");
   Latex.DrawLatex(0.10, 0.915, "#color[1]{Good} #color[2]{Fake}");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched.SetStats(0);
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch.SetStats(0);
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156.SetStats(0);
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156.SetStats(0);
   HJetEtaPhi_GoodTrackAlgoFraction_PT50.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT50.SetStats(0);
   HJetEtaPhi_GoodTrackAlgoFraction_PT70.SetStats(0);
   HJetEtaPhi_BadTrackAlgoFraction_PT70.SetStats(0);
   
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched, "colz");
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch, "colz");
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156, "colz");
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156, "colz");
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT50, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT50, "colz");
   PdfFile.AddPlot(HJetEtaPhi_GoodTrackAlgoFraction_PT70, "colz");
   PdfFile.AddPlot(HJetEtaPhi_BadTrackAlgoFraction_PT70, "colz");

   TH2D HWorldPF("HWorldPF", ";p_{T};", 100, 0, 75, 100, 1e-8, 1);
   HWorldPF.SetStats(0);

   TLegend LegendPF(0.5, 0.8, 0.8, 0.6);
   LegendPF.SetTextFont(42);
   LegendPF.SetTextSize(0.035);
   LegendPF.SetBorderSize(0);
   LegendPF.SetFillStyle(0);
   LegendPF.AddEntry(&HPFPT_ID1_EtaN25N15, "-2.5 < #eta < -1.5", "l");
   LegendPF.AddEntry(&HPFPT_ID1_EtaN15P15, "-1.5 < #eta < 1.5", "l");
   LegendPF.AddEntry(&HPFPT_ID1_EtaP15P25, "1.5 < #eta < 2.5", "l");

   HWorldPF.SetTitle("ID = 1");
   HWorldPF.Draw("axis");
   HPFPT_ID1_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID1_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID1_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID1_EtaN25N15.DrawNormalized("same");
   HPFPT_ID1_EtaN15P15.DrawNormalized("same");
   HPFPT_ID1_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 2");
   HWorldPF.Draw("axis");
   HPFPT_ID2_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID2_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID2_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID2_EtaN25N15.DrawNormalized("same");
   HPFPT_ID2_EtaN15P15.DrawNormalized("same");
   HPFPT_ID2_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 3");
   HWorldPF.Draw("axis");
   HPFPT_ID3_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID3_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID3_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID3_EtaN25N15.DrawNormalized("same");
   HPFPT_ID3_EtaN15P15.DrawNormalized("same");
   HPFPT_ID3_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 4");
   HWorldPF.Draw("axis");
   HPFPT_ID4_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID4_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID4_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID4_EtaN25N15.DrawNormalized("same");
   HPFPT_ID4_EtaN15P15.DrawNormalized("same");
   HPFPT_ID4_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 5");
   HWorldPF.Draw("axis");
   HPFPT_ID5_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID5_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID5_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID5_EtaN25N15.DrawNormalized("same");
   HPFPT_ID5_EtaN15P15.DrawNormalized("same");
   HPFPT_ID5_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 6");
   HWorldPF.Draw("axis");
   HPFPT_ID6_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID6_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID6_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID6_EtaN25N15.DrawNormalized("same");
   HPFPT_ID6_EtaN15P15.DrawNormalized("same");
   HPFPT_ID6_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HWorldPF.SetTitle("ID = 7");
   HWorldPF.Draw("axis");
   HPFPT_ID7_EtaN25N15.SetLineColor(kBlack);
   HPFPT_ID7_EtaN15P15.SetLineColor(kGreen);
   HPFPT_ID7_EtaP15P25.SetLineColor(kRed);
   HPFPT_ID7_EtaN25N15.DrawNormalized("same");
   HPFPT_ID7_EtaN15P15.DrawNormalized("same");
   HPFPT_ID7_EtaP15P25.DrawNormalized("same");
   LegendPF.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HPFEtaPhi_ID1_PT05.SetStats(0);
   HPFEtaPhi_ID2_PT05.SetStats(0);
   HPFEtaPhi_ID3_PT05.SetStats(0);
   HPFEtaPhi_ID4_PT05.SetStats(0);
   HPFEtaPhi_ID5_PT05.SetStats(0);
   HPFEtaPhi_ID6_PT05.SetStats(0);
   HPFEtaPhi_ID7_PT05.SetStats(0);
   HPFEtaPhi_ID1_PT10.SetStats(0);
   HPFEtaPhi_ID2_PT10.SetStats(0);
   HPFEtaPhi_ID3_PT10.SetStats(0);
   HPFEtaPhi_ID4_PT10.SetStats(0);
   HPFEtaPhi_ID5_PT10.SetStats(0);
   HPFEtaPhi_ID6_PT10.SetStats(0);
   HPFEtaPhi_ID7_PT10.SetStats(0);
   HPFEtaPhi_ID1_PT20.SetStats(0);
   HPFEtaPhi_ID2_PT20.SetStats(0);
   HPFEtaPhi_ID3_PT20.SetStats(0);
   HPFEtaPhi_ID4_PT20.SetStats(0);
   HPFEtaPhi_ID5_PT20.SetStats(0);
   HPFEtaPhi_ID6_PT20.SetStats(0);
   HPFEtaPhi_ID7_PT20.SetStats(0);
   HPFEtaPhi_ID1_PT50.SetStats(0);
   HPFEtaPhi_ID2_PT50.SetStats(0);
   HPFEtaPhi_ID3_PT50.SetStats(0);
   HPFEtaPhi_ID4_PT50.SetStats(0);
   HPFEtaPhi_ID5_PT50.SetStats(0);
   HPFEtaPhi_ID6_PT50.SetStats(0);
   HPFEtaPhi_ID7_PT50.SetStats(0);
   HPFEtaPhi_ID1_PT100.SetStats(0);
   HPFEtaPhi_ID2_PT100.SetStats(0);
   HPFEtaPhi_ID3_PT100.SetStats(0);
   HPFEtaPhi_ID4_PT100.SetStats(0);
   HPFEtaPhi_ID5_PT100.SetStats(0);
   HPFEtaPhi_ID6_PT100.SetStats(0);
   HPFEtaPhi_ID7_PT100.SetStats(0);
   HPFEtaPhi_ID1_PT200.SetStats(0);
   HPFEtaPhi_ID2_PT200.SetStats(0);
   HPFEtaPhi_ID3_PT200.SetStats(0);
   HPFEtaPhi_ID4_PT200.SetStats(0);
   HPFEtaPhi_ID5_PT200.SetStats(0);
   HPFEtaPhi_ID6_PT200.SetStats(0);
   HPFEtaPhi_ID7_PT200.SetStats(0);
   HPFEtaPhi_ID1_PT500.SetStats(0);
   HPFEtaPhi_ID2_PT500.SetStats(0);
   HPFEtaPhi_ID3_PT500.SetStats(0);
   HPFEtaPhi_ID4_PT500.SetStats(0);
   HPFEtaPhi_ID5_PT500.SetStats(0);
   HPFEtaPhi_ID6_PT500.SetStats(0);
   HPFEtaPhi_ID7_PT500.SetStats(0);

   HPFEtaPhi_Peripheral_ID1_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT05.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT10.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT20.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT50.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT100.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT200.SetStats(0);
   HPFEtaPhi_Peripheral_ID1_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID2_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID3_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID4_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID5_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID6_PT500.SetStats(0);
   HPFEtaPhi_Peripheral_ID7_PT500.SetStats(0);

   PdfFile.AddPlot(HPFEtaPhi_ID1_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID1_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID2_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID3_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID4_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID5_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID6_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_ID7_PT500, "colz");

   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT05, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT10, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT20, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT50, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT100, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT200, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID1_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID2_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID3_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID4_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID5_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID6_PT500, "colz");
   PdfFile.AddPlot(HPFEtaPhi_Peripheral_ID7_PT500, "colz");

   OutputFile.cd();

   HN.Write();
   HJetEtaPhiPT30.Write();
   HJetEtaPhiPT50.Write();
   HJetEtaPhiPT70.Write();
   HJetEtaPhiPT100.Write();
   
   HJetEtaPhiPT70FailL156.Write();
   HJetEtaPhiPT80FailL156.Write();
   HJetEtaPhiPT100FailL156.Write();
   HJetEtaPhiPT120FailL156.Write();

   HJetPT.Write();
   HJetPT_EtaN15P15.Write();
   HJetPT_EtaN25P25.Write();
   HJetPT_EtaN00P25.Write();
   HJetPT_EtaN25P00.Write();
   HJetPT_EtaP15P25.Write();
   HJetPT_EtaN25N15.Write();
   HJetPTPassL156.Write();
   HJetPTPassL156_EtaN15P15.Write();
   HJetPTPassL156_EtaN25P25.Write();
   HJetPTPassL156_EtaN00P25.Write();
   HJetPTPassL156_EtaN25P00.Write();
   HJetPTPassL156_EtaP15P25.Write();
   HJetPTPassL156_EtaN25N15.Write();

   HJetPTVsRawPT.Write();
   HRawPTVsJEC.Write();
                  
   HAllJetPT_EtaN25N15.Write();
   HAllJetPT_EtaN15P15.Write();
   HAllJetPT_EtaP15P25.Write();
   
   HJetCHF_PT50_EtaN25N15.Write();
   HJetCHF_PT50_EtaN15P15.Write();
   HJetCHF_PT50_EtaP15P25.Write();
   HJetCEF_PT50_EtaN25N15.Write();
   HJetCEF_PT50_EtaN15P15.Write();
   HJetCEF_PT50_EtaP15P25.Write();
   HJetNHF_PT50_EtaN25N15.Write();
   HJetNHF_PT50_EtaN15P15.Write();
   HJetNHF_PT50_EtaP15P25.Write();
   HJetNEF_PT50_EtaN25N15.Write();
   HJetNEF_PT50_EtaN15P15.Write();
   HJetNEF_PT50_EtaP15P25.Write();
   HJetMUF_PT50_EtaN25N15.Write();
   HJetMUF_PT50_EtaN15P15.Write();
   HJetMUF_PT50_EtaP15P25.Write();
   HJetCH_PT50_EtaN25N15.Write();
   HJetCH_PT50_EtaN15P15.Write();
   HJetCH_PT50_EtaP15P25.Write();
   HJetCE_PT50_EtaN25N15.Write();
   HJetCE_PT50_EtaN15P15.Write();
   HJetCE_PT50_EtaP15P25.Write();
   HJetNH_PT50_EtaN25N15.Write();
   HJetNH_PT50_EtaN15P15.Write();
   HJetNH_PT50_EtaP15P25.Write();
   HJetNE_PT50_EtaN25N15.Write();
   HJetNE_PT50_EtaN15P15.Write();
   HJetNE_PT50_EtaP15P25.Write();
   HJetMU_PT50_EtaN25N15.Write();
   HJetMU_PT50_EtaN15P15.Write();
   HJetMU_PT50_EtaP15P25.Write();
   HJetCHF_PT70_EtaN25N15.Write();
   HJetCHF_PT70_EtaN15P15.Write();
   HJetCHF_PT70_EtaP15P25.Write();
   HJetCEF_PT70_EtaN25N15.Write();
   HJetCEF_PT70_EtaN15P15.Write();
   HJetCEF_PT70_EtaP15P25.Write();
   HJetNHF_PT70_EtaN25N15.Write();
   HJetNHF_PT70_EtaN15P15.Write();
   HJetNHF_PT70_EtaP15P25.Write();
   HJetNEF_PT70_EtaN25N15.Write();
   HJetNEF_PT70_EtaN15P15.Write();
   HJetNEF_PT70_EtaP15P25.Write();
   HJetMUF_PT70_EtaN25N15.Write();
   HJetMUF_PT70_EtaN15P15.Write();
   HJetMUF_PT70_EtaP15P25.Write();
   HJetCH_PT70_EtaN25N15.Write();
   HJetCH_PT70_EtaN15P15.Write();
   HJetCH_PT70_EtaP15P25.Write();
   HJetCE_PT70_EtaN25N15.Write();
   HJetCE_PT70_EtaN15P15.Write();
   HJetCE_PT70_EtaP15P25.Write();
   HJetNH_PT70_EtaN25N15.Write();
   HJetNH_PT70_EtaN15P15.Write();
   HJetNH_PT70_EtaP15P25.Write();
   HJetNE_PT70_EtaN25N15.Write();
   HJetNE_PT70_EtaN15P15.Write();
   HJetNE_PT70_EtaP15P25.Write();
   HJetMU_PT70_EtaN25N15.Write();
   HJetMU_PT70_EtaN15P15.Write();
   HJetMU_PT70_EtaP15P25.Write();

   HCaloPFMatchDR_PassL156.Write();
   HCaloPFMatchDR_FailL156.Write();

   HTrackAlgo_PT70_Matched.Write();
   HTrackAlgo_PT70_NonMatch.Write();
   HTrackPT_Algo6_PT70_Matched.Write();
   HTrackPT_Algo6_PT70_NonMatch.Write();
   HTrackMVA_Algo6_PT70_Matched.Write();
   HTrackMVA_Algo6_PT70_NonMatch.Write();
   HTrackMVA_Algo6MinPT_PT70_Matched.Write();
   HTrackMVA_Algo6MinPT_PT70_NonMatch.Write();
   HTrackPTVsMVA_Algo6_PT70_Matched.Write();
   HTrackPTVsMVA_Algo6_PT70_NonMatch.Write();
   HTrackAlgo_PT80_Matched.Write();
   HTrackAlgo_PT80_NonMatch.Write();
   HTrackPT_Algo6_PT80_Matched.Write();
   HTrackPT_Algo6_PT80_NonMatch.Write();
   HTrackMVA_Algo6_PT80_Matched.Write();
   HTrackMVA_Algo6_PT80_NonMatch.Write();
   HTrackMVA_Algo6MinPT_PT80_Matched.Write();
   HTrackMVA_Algo6MinPT_PT80_NonMatch.Write();
   HTrackPTVsMVA_Algo6_PT80_Matched.Write();
   HTrackPTVsMVA_Algo6_PT80_NonMatch.Write();
   HTrackAlgo_PT100_Matched.Write();
   HTrackAlgo_PT100_NonMatch.Write();
   HTrackPT_Algo6_PT100_Matched.Write();
   HTrackPT_Algo6_PT100_NonMatch.Write();
   HTrackMVA_Algo6_PT100_Matched.Write();
   HTrackMVA_Algo6_PT100_NonMatch.Write();
   HTrackMVA_Algo6MinPT_PT100_Matched.Write();
   HTrackMVA_Algo6MinPT_PT100_NonMatch.Write();
   HTrackPTVsMVA_Algo6_PT100_Matched.Write();
   HTrackPTVsMVA_Algo6_PT100_NonMatch.Write();

   HTrackAlgo6Fraction_PT70_Matched.Write();
   HTrackAlgo6Fraction_PT70_NonMatch.Write();
   HTrackAlgo6Fraction_PT80_Matched.Write();
   HTrackAlgo6Fraction_PT80_NonMatch.Write();
   HTrackAlgo6Fraction_PT100_Matched.Write();
   HTrackAlgo6Fraction_PT100_NonMatch.Write();
   HTrackAlgo6Fraction_PT70_PassL156.Write();
   HTrackAlgo6Fraction_PT70_FailL156.Write();
   HTrackAlgo6Fraction_PT80_PassL156.Write();
   HTrackAlgo6Fraction_PT80_FailL156.Write();
   HTrackAlgo6Fraction_PT100_PassL156.Write();
   HTrackAlgo6Fraction_PT100_FailL156.Write();
   HTrackAlgo6Fraction_MinPT_PT70_Matched.Write();
   HTrackAlgo6Fraction_MinPT_PT70_NonMatch.Write();
   HTrackAlgo6Fraction_MinPT_PT80_Matched.Write();
   HTrackAlgo6Fraction_MinPT_PT80_NonMatch.Write();
   HTrackAlgo6Fraction_MinPT_PT100_Matched.Write();
   HTrackAlgo6Fraction_MinPT_PT100_NonMatch.Write();
   HTrackAlgo6Fraction_MVA095_PT70_Matched.Write();
   HTrackAlgo6Fraction_MVA095_PT70_NonMatch.Write();
   HTrackAlgo6Fraction_MVA095_PT80_Matched.Write();
   HTrackAlgo6Fraction_MVA095_PT80_NonMatch.Write();
   HTrackAlgo6Fraction_MVA095_PT100_Matched.Write();
   HTrackAlgo6Fraction_MVA095_PT100_NonMatch.Write();
   HTrackAlgo6Fraction_MVA098_PT70_Matched.Write();
   HTrackAlgo6Fraction_MVA098_PT70_NonMatch.Write();
   HTrackAlgo6Fraction_MVA098_PT80_Matched.Write();
   HTrackAlgo6Fraction_MVA098_PT80_NonMatch.Write();
   HTrackAlgo6Fraction_MVA098_PT100_Matched.Write();
   HTrackAlgo6Fraction_MVA098_PT100_NonMatch.Write();

   HJetEtaPhi_GoodTrackAlgoFraction_PT70_Matched.Write();
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_NonMatch.Write();
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_PassL156.Write();
   HJetEtaPhi_GoodTrackAlgoFraction_PT70_FailL156.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT70_Matched.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT70_NonMatch.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT70_PassL156.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT70_FailL156.Write();
   HJetEtaPhi_GoodTrackAlgoFraction_PT50.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT50.Write();
   HJetEtaPhi_GoodTrackAlgoFraction_PT70.Write();
   HJetEtaPhi_BadTrackAlgoFraction_PT70.Write();

   HPFPT_ID1_EtaN25N15.Write();
   HPFPT_ID1_EtaN15P15.Write();
   HPFPT_ID1_EtaP15P25.Write();
   HPFPT_ID2_EtaN25N15.Write();
   HPFPT_ID2_EtaN15P15.Write();
   HPFPT_ID2_EtaP15P25.Write();
   HPFPT_ID3_EtaN25N15.Write();
   HPFPT_ID3_EtaN15P15.Write();
   HPFPT_ID3_EtaP15P25.Write();
   HPFPT_ID4_EtaN25N15.Write();
   HPFPT_ID4_EtaN15P15.Write();
   HPFPT_ID4_EtaP15P25.Write();
   HPFPT_ID5_EtaN25N15.Write();
   HPFPT_ID5_EtaN15P15.Write();
   HPFPT_ID5_EtaP15P25.Write();
   HPFPT_ID6_EtaN25N15.Write();
   HPFPT_ID6_EtaN15P15.Write();
   HPFPT_ID6_EtaP15P25.Write();
   HPFPT_ID7_EtaN25N15.Write();
   HPFPT_ID7_EtaN15P15.Write();
   HPFPT_ID7_EtaP15P25.Write();

   HPFEtaPhi_ID1_PT05.Write();
   HPFEtaPhi_ID2_PT05.Write();
   HPFEtaPhi_ID3_PT05.Write();
   HPFEtaPhi_ID4_PT05.Write();
   HPFEtaPhi_ID5_PT05.Write();
   HPFEtaPhi_ID6_PT05.Write();
   HPFEtaPhi_ID7_PT05.Write();
   HPFEtaPhi_ID1_PT10.Write();
   HPFEtaPhi_ID2_PT10.Write();
   HPFEtaPhi_ID3_PT10.Write();
   HPFEtaPhi_ID4_PT10.Write();
   HPFEtaPhi_ID5_PT10.Write();
   HPFEtaPhi_ID6_PT10.Write();
   HPFEtaPhi_ID7_PT10.Write();
   HPFEtaPhi_ID1_PT20.Write();
   HPFEtaPhi_ID2_PT20.Write();
   HPFEtaPhi_ID3_PT20.Write();
   HPFEtaPhi_ID4_PT20.Write();
   HPFEtaPhi_ID5_PT20.Write();
   HPFEtaPhi_ID6_PT20.Write();
   HPFEtaPhi_ID7_PT20.Write();
   HPFEtaPhi_ID1_PT50.Write();
   HPFEtaPhi_ID2_PT50.Write();
   HPFEtaPhi_ID3_PT50.Write();
   HPFEtaPhi_ID4_PT50.Write();
   HPFEtaPhi_ID5_PT50.Write();
   HPFEtaPhi_ID6_PT50.Write();
   HPFEtaPhi_ID7_PT50.Write();
   HPFEtaPhi_ID1_PT100.Write();
   HPFEtaPhi_ID2_PT100.Write();
   HPFEtaPhi_ID3_PT100.Write();
   HPFEtaPhi_ID4_PT100.Write();
   HPFEtaPhi_ID5_PT100.Write();
   HPFEtaPhi_ID6_PT100.Write();
   HPFEtaPhi_ID7_PT100.Write();
   HPFEtaPhi_ID1_PT200.Write();
   HPFEtaPhi_ID2_PT200.Write();
   HPFEtaPhi_ID3_PT200.Write();
   HPFEtaPhi_ID4_PT200.Write();
   HPFEtaPhi_ID5_PT200.Write();
   HPFEtaPhi_ID6_PT200.Write();
   HPFEtaPhi_ID7_PT200.Write();
   HPFEtaPhi_ID1_PT500.Write();
   HPFEtaPhi_ID2_PT500.Write();
   HPFEtaPhi_ID3_PT500.Write();
   HPFEtaPhi_ID4_PT500.Write();
   HPFEtaPhi_ID5_PT500.Write();
   HPFEtaPhi_ID6_PT500.Write();
   HPFEtaPhi_ID7_PT500.Write();

   HPFEtaPhi_Peripheral_ID1_PT05.Write();
   HPFEtaPhi_Peripheral_ID2_PT05.Write();
   HPFEtaPhi_Peripheral_ID3_PT05.Write();
   HPFEtaPhi_Peripheral_ID4_PT05.Write();
   HPFEtaPhi_Peripheral_ID5_PT05.Write();
   HPFEtaPhi_Peripheral_ID6_PT05.Write();
   HPFEtaPhi_Peripheral_ID7_PT05.Write();
   HPFEtaPhi_Peripheral_ID1_PT10.Write();
   HPFEtaPhi_Peripheral_ID2_PT10.Write();
   HPFEtaPhi_Peripheral_ID3_PT10.Write();
   HPFEtaPhi_Peripheral_ID4_PT10.Write();
   HPFEtaPhi_Peripheral_ID5_PT10.Write();
   HPFEtaPhi_Peripheral_ID6_PT10.Write();
   HPFEtaPhi_Peripheral_ID7_PT10.Write();
   HPFEtaPhi_Peripheral_ID1_PT20.Write();
   HPFEtaPhi_Peripheral_ID2_PT20.Write();
   HPFEtaPhi_Peripheral_ID3_PT20.Write();
   HPFEtaPhi_Peripheral_ID4_PT20.Write();
   HPFEtaPhi_Peripheral_ID5_PT20.Write();
   HPFEtaPhi_Peripheral_ID6_PT20.Write();
   HPFEtaPhi_Peripheral_ID7_PT20.Write();
   HPFEtaPhi_Peripheral_ID1_PT50.Write();
   HPFEtaPhi_Peripheral_ID2_PT50.Write();
   HPFEtaPhi_Peripheral_ID3_PT50.Write();
   HPFEtaPhi_Peripheral_ID4_PT50.Write();
   HPFEtaPhi_Peripheral_ID5_PT50.Write();
   HPFEtaPhi_Peripheral_ID6_PT50.Write();
   HPFEtaPhi_Peripheral_ID7_PT50.Write();
   HPFEtaPhi_Peripheral_ID1_PT100.Write();
   HPFEtaPhi_Peripheral_ID2_PT100.Write();
   HPFEtaPhi_Peripheral_ID3_PT100.Write();
   HPFEtaPhi_Peripheral_ID4_PT100.Write();
   HPFEtaPhi_Peripheral_ID5_PT100.Write();
   HPFEtaPhi_Peripheral_ID6_PT100.Write();
   HPFEtaPhi_Peripheral_ID7_PT100.Write();
   HPFEtaPhi_Peripheral_ID1_PT200.Write();
   HPFEtaPhi_Peripheral_ID2_PT200.Write();
   HPFEtaPhi_Peripheral_ID3_PT200.Write();
   HPFEtaPhi_Peripheral_ID4_PT200.Write();
   HPFEtaPhi_Peripheral_ID5_PT200.Write();
   HPFEtaPhi_Peripheral_ID6_PT200.Write();
   HPFEtaPhi_Peripheral_ID7_PT200.Write();
   HPFEtaPhi_Peripheral_ID1_PT500.Write();
   HPFEtaPhi_Peripheral_ID2_PT500.Write();
   HPFEtaPhi_Peripheral_ID3_PT500.Write();
   HPFEtaPhi_Peripheral_ID4_PT500.Write();
   HPFEtaPhi_Peripheral_ID5_PT500.Write();
   HPFEtaPhi_Peripheral_ID6_PT500.Write();
   HPFEtaPhi_Peripheral_ID7_PT500.Write();

   OutputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



