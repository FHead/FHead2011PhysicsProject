#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void Add1DPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName,
   string Title, double XMin, double XMax, double YMin, double YMax, bool LogY = false, bool Normalize = true);
void Add1DProfilePlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName,
   string Title, double XMin, double XMax, double YMin, double YMax, bool LogY = false);
void Add2DPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName, string Title,
   bool LogZ = false, bool Normalize = true);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileNameTarget = CL.Get("InputTarget");
   string InputFileNameReference = CL.Get("InputReference");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Validation Comparison");

   TFile F1(InputFileNameTarget.c_str());
   TFile F2(InputFileNameReference.c_str());

   PdfFile.AddTextPage("Jet Plots");
   
   Add1DPlot(PdfFile, F1, F2, "HJetPT", "Inclusive jet PT;p_{T};", 0, 200, 1e-5, 1, true);
   
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT30", "Jet occupancy, PT > 30");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT50", "Jet occupancy, PT > 50");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT75", "Jet occupancy, PT > 75");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT100", "Jet occupancy, PT > 100");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT125", "Jet occupancy, PT > 125");

   Add1DPlot(PdfFile, F1, F2, "HJetEtaPT30", "Jet PT > 30;#eta;", -2.5, 2.5, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetEtaPT50", "Jet PT > 50;#eta;", -2.5, 2.5, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetEtaPT75", "Jet PT > 75;#eta;", -2.5, 2.5, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetEtaPT100", "Jet PT > 100;#eta;", -2.5, 2.5, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetEtaPT125", "Jet PT > 125;#eta;", -2.5, 2.5, 0, 0.03);
   
   Add1DPlot(PdfFile, F1, F2, "HJetPTEtaN25N15", "Jet PT, -2.5 < #eta < -1.5;p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HJetPTEtaN15N00", "Jet PT, -1.5 < #eta < 0.0;p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HJetPTEtaP00P15", "Jet PT, 0.0 < #eta < 1.5;p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HJetPTEtaP15P25", "Jet PT, 1.5 < #eta < 2.5;p_{T};", 0, 200, 1e-5, 1, true);

   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT30EtaN25N15", "PT > 30, -2.5 < #eta < -1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT30EtaN15N00", "PT > 30, -1.5 < #eta < 0.0;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT30EtaP00P15", "PT > 30, 0.0 < #eta < 1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT30EtaP15P25", "PT > 30, 1.5 < #eta < 2.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT50EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT50EtaN15N00", "PT > 50, -1.5 < #eta < 0.0;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT50EtaP00P15", "PT > 50, 0.0 < #eta < 1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT50EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT75EtaN25N15", "PT > 75, -2.5 < #eta < -1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT75EtaN15N00", "PT > 75, -1.5 < #eta < 0.0;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT75EtaP00P15", "PT > 75, 0.0 < #eta < 1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT75EtaP15P25", "PT > 75, 1.5 < #eta < 2.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT100EtaN25N15", "PT > 100, -2.5 < #eta < -1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT100EtaN15N00", "PT > 100, -1.5 < #eta < 0.0;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT100EtaP00P15", "PT > 100, 0.0 < #eta < 1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT100EtaP15P25", "PT > 100, 1.5 < #eta < 2.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT125EtaN25N15", "PT > 125, -2.5 < #eta < -1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT125EtaN15N00", "PT > 125, -1.5 < #eta < 0.0;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT125EtaP00P15", "PT > 125, 0.0 < #eta < 1.5;#phi;", -M_PI, M_PI, 0, 0.03);
   Add1DPlot(PdfFile, F1, F2, "HJetPhiPT125EtaP15P25", "PT > 125, 1.5 < #eta < 2.5;#phi;", -M_PI, M_PI, 0, 0.03);

   Add2DPlot(PdfFile, F1, F2, "HRawPTVsJEC", "Raw PT vs JEC");
   Add2DPlot(PdfFile, F1, F2, "HRawPTVsJetPT", "Raw PT vs Jet PT");

   Add1DProfilePlot(PdfFile, F1, F2, "HJetEtaVsResponseGenPT30PT50", "30 < p_{T}^{Gen} < 50;#eta;Response", -2.5, 2.5, 0.50, 1.50, false);
   Add1DProfilePlot(PdfFile, F1, F2, "HJetEtaVsResponseGenPT50PT75", "50 < p_{T}^{Gen} < 75;#eta;Response", -2.5, 2.5, 0.50, 1.50, false);
   Add1DProfilePlot(PdfFile, F1, F2, "HJetEtaVsResponseGenPT75PT100", "75 < p_{T}^{Gen} < 100;#eta;Response", -2.5, 2.5, 0.50, 1.50, false);
   Add1DProfilePlot(PdfFile, F1, F2, "HJetEtaVsResponseGenPT100PT125", "100 < p_{T}^{Gen} < 125;#eta;Response", -2.5, 2.5, 0.50, 1.50, false);
   
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT30FailL156", "PT > 30, fail L1_SingleJet56");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT50FailL156", "PT > 50, fail L1_SingleJet56");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT75FailL156", "PT > 75, fail L1_SingleJet56");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT100FailL156", "PT > 100, fail L1_SingleJet56");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT125FailL156", "PT > 125, fail L1_SingleJet56");

   PdfFile.AddTextPage("PF fractions");

   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT50EtaN25N15", "CHF, -2.5 < #eta < -1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT50EtaN15N00", "CHF, -1.5 < #eta < 0.0, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT50EtaP00P15", "CHF, 0.0 < #eta < 1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT50EtaP15P25", "CHF, 1.5 < #eta < 2.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT50EtaN25N15", "CEF, -2.5 < #eta < -1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT50EtaN15N00", "CEF, -1.5 < #eta < 0.0, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT50EtaP00P15", "CEF, 0.0 < #eta < 1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT50EtaP15P25", "CEF, 1.5 < #eta < 2.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT50EtaN25N15", "NHF, -2.5 < #eta < -1.5, JetPT > 50", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT50EtaN15N00", "NHF, -1.5 < #eta < 0.0, JetPT > 50", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT50EtaP00P15", "NHF, 0.0 < #eta < 1.5, JetPT > 50", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT50EtaP15P25", "NHF, 1.5 < #eta < 2.5, JetPT > 50", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT50EtaN25N15", "NEF, -2.5 < #eta < -1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT50EtaN15N00", "NEF, -1.5 < #eta < 0.0, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT50EtaP00P15", "NEF, 0.0 < #eta < 1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT50EtaP15P25", "NEF, 1.5 < #eta < 2.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT50EtaN25N15", "MUF, -2.5 < #eta < -1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT50EtaN15N00", "MUF, -1.5 < #eta < 0.0, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT50EtaP00P15", "MUF, 0.0 < #eta < 1.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT50EtaP15P25", "MUF, 1.5 < #eta < 2.5, JetPT > 50", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT70EtaN25N15", "CHF, -2.5 < #eta < -1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT70EtaN15N00", "CHF, -1.5 < #eta < 0.0, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT70EtaP00P15", "CHF, 0.0 < #eta < 1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCHFPT70EtaP15P25", "CHF, 1.5 < #eta < 2.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT70EtaN25N15", "CEF, -2.5 < #eta < -1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT70EtaN15N00", "CEF, -1.5 < #eta < 0.0, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT70EtaP00P15", "CEF, 0.0 < #eta < 1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetCEFPT70EtaP15P25", "CEF, 1.5 < #eta < 2.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT70EtaN25N15", "NHF, -2.5 < #eta < -1.5, JetPT > 70", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT70EtaN15N00", "NHF, -1.5 < #eta < 0.0, JetPT > 70", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT70EtaP00P15", "NHF, 0.0 < #eta < 1.5, JetPT > 70", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNHFPT70EtaP15P25", "NHF, 1.5 < #eta < 2.5, JetPT > 70", 0, 1, 0, 0.45);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT70EtaN25N15", "NEF, -2.5 < #eta < -1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT70EtaN15N00", "NEF, -1.5 < #eta < 0.0, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT70EtaP00P15", "NEF, 0.0 < #eta < 1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetNEFPT70EtaP15P25", "NEF, 1.5 < #eta < 2.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT70EtaN25N15", "MUF, -2.5 < #eta < -1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT70EtaN15N00", "MUF, -1.5 < #eta < 0.0, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT70EtaP00P15", "MUF, 0.0 < #eta < 1.5, JetPT > 70", 0, 1, 0, 0.15);
   Add1DPlot(PdfFile, F1, F2, "HJetMUFPT70EtaP15P25", "MUF, 1.5 < #eta < 2.5, JetPT > 70", 0, 1, 0, 0.15);

   PdfFile.AddTextPage("Jet ID distributions");

   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT30PassL156",
      "JetPT > 30, Pass L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT50PassL156",
      "JetPT > 50, Pass L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT70PassL156",
      "JetPT > 70, Pass L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT80PassL156",
      "JetPT > 80, Pass L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT100PassL156",
      "JetPT > 100, Pass L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT30FailL156",
      "JetPT > 30, Fail L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT50FailL156",
      "JetPT > 50, Fail L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT70FailL156",
      "JetPT > 70, Fail L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT80FailL156",
      "JetPT > 80, Fail L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);
   Add1DPlot(PdfFile, F1, F2, "HJetAlgo6FractionPT100FailL156",
      "JetPT > 100, Fail L1_SingleJet56;Algo6 Fraction;", 0, 1, 1e-5, 2.50, true);

   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT50GoodID", "PT > 50, ID good");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT50BadID",  "PT > 50, ID bad");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT70GoodID", "PT > 70, ID good");
   Add2DPlot(PdfFile, F1, F2, "HJetEtaPhiPT70BadID",  "PT > 70, ID bad");

   PdfFile.AddTextPage("Track distributions");

   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID4PT1", "Initial step, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID4PT2", "Initial step, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID4PT5", "Initial step, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID4PT10", "Initial step, PT > 10");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID5PT1", "Low PT triplet, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID5PT2", "Low PT triplet, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID5PT5", "Low PT triplet, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID5PT10", "Low PT triplet, PT > 10");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID6PT1", "Pixel pair, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID6PT2", "Pixel pair, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID6PT5", "Pixel pair, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID6PT10", "Pixel pair, PT > 10");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID7PT1", "Detached triplet, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID7PT2", "Detached triplet, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID7PT5", "Detached triplet, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID7PT10", "Detached triplet, PT > 10");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID22PT1", "High PT triplet, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID22PT2", "High PT triplet, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID22PT5", "High PT triplet, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID22PT10", "High PT triplet, PT > 10");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID23PT1", "Low PT quadruplet, PT > 1");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID23PT2", "Low PT quadruplet, PT > 2");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID23PT5", "Low PT quadruplet, PT > 5");
   Add2DPlot(PdfFile, F1, F2, "HTrackEtaPhiID23PT10", "Low PT quadruplet, PT > 10");

   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID4", "Inital step;MVA;", 0.00, 1.00, 0.00, 0.10);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID5", "Low PT triplet;MVA;", 0.40, 1.00, 0.00, 0.05);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID6", "Pixel pair;MVA;", 0.85, 1.00, 0.00, 0.25);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID6", "Pixel pair;MVA;", 0.85, 1.00, 1e-4, 0.50, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID7", "Detached triplet;MVA;", 0.80, 1.00, 0.00, 0.10);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID22", "High PT triplet;MVA;", 0.80, 1.00, 0.00, 0.10);
   Add1DPlot(PdfFile, F1, F2, "HTrackMVAID23", "Low PT quadruplet;MVA;", 0.00, 1.00, 0.00, 0.05);

   Add1DPlot(PdfFile, F1, F2, "HTrackMET", "Track MET;MET;", 0, 700, 1e-5, 0.2, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackMETX", "Track MET ((1,1) direction);MET;", -500, 500, 1e-5, 0.2, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackMETY", "Track MET ((1,-1) direction);MET;", -500, 500, 1e-5, 0.2, true);
   Add1DPlot(PdfFile, F1, F2, "HPositiveTrackMET", "Positive Track MET;MET;", 0, 700, 1e-5, 0.2, true);
   Add1DPlot(PdfFile, F1, F2, "HPositiveTrackMETX", "Positive Track MET ((1,1) direction);MET;", -500, 500, 1e-5, 0.2, true);
   Add1DPlot(PdfFile, F1, F2, "HPositiveTrackMETY", "Positive Track MET ((1,-1) direction);MET;", -500, 500, 1e-5, 0.2, true);

   PdfFile.AddTextPage("Track jets");

   Add2DPlot(PdfFile, F1, F2, "HTrackJetEtaPhiPT30", "Track jet PT > 30");
   Add2DPlot(PdfFile, F1, F2, "HTrackJetEtaPhiPT50", "Track jet PT > 50");
   Add2DPlot(PdfFile, F1, F2, "HTrackJetEtaPhiPT75", "Track jet PT > 75");
   Add2DPlot(PdfFile, F1, F2, "HTrackJetEtaPhiPT100", "Track jet PT > 100");
   Add2DPlot(PdfFile, F1, F2, "HTrackJetEtaPhiPT125", "Track jet PT > 125");

   Add1DPlot(PdfFile, F1, F2, "HTrackJetPTEtaN25N15", "-2.5 < #eta < -1.5;Track jet p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackJetPTEtaN15N00", "-1.5 < #eta < 0.0;Track jet p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackJetPTEtaP00P15", "0.0 < #eta < 1.5;Track jet p_{T};", 0, 200, 1e-5, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HTrackJetPTEtaP15P25", "1.5 < #eta < 2.5;Track jet p_{T};", 0, 200, 1e-5, 1, true);

   PdfFile.AddTextPage("PF candidate distributions");

   Add1DPlot(PdfFile, F1, F2, "HPFPTID1EtaN25N15", "-2.5 < #eta < -1.5, ID = 1;p_{T};", 0, 75, 1e-7, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID1EtaN15N00", "-1.5 < #eta < 0.0, ID = 1;p_{T};", 0, 75, 1e-7, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID1EtaP00P15", "0.0 < #eta < 1.5, ID = 1;p_{T};", 0, 75, 1e-7, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID1EtaP15P25", "1.5 < #eta < 2.5, ID = 1;p_{T};", 0, 75, 1e-7, 1, true);
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID1PT05", "ID = 1, PT > 0.5");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID1PT1", "ID = 1, PT > 1.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID1PT2", "ID = 1, PT > 2.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID1PT5", "ID = 1, PT > 5.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID1PT10", "ID = 1, PT > 10.0");
   Add1DPlot(PdfFile, F1, F2, "HPFPTID2EtaN25N15", "-2.5 < #eta < -1.5, ID = 2;p_{T};", 0, 75, 1e-3, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID2EtaN15N00", "-1.5 < #eta < 0.0, ID = 2;p_{T};", 0, 75, 1e-3, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID2EtaP00P15", "0.0 < #eta < 1.5, ID = 2;p_{T};", 0, 75, 1e-3, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID2EtaP15P25", "1.5 < #eta < 2.5, ID = 2;p_{T};", 0, 75, 1e-3, 1, true);
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID2PT05", "ID = 2, PT > 0.5");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID2PT1", "ID = 2, PT > 1.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID2PT2", "ID = 2, PT > 2.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID2PT5", "ID = 2, PT > 5.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID2PT10", "ID = 2, PT > 10.0");
   Add1DPlot(PdfFile, F1, F2, "HPFPTID3EtaN25N15", "-2.5 < #eta < -1.5, ID = 3;p_{T};", 0, 75, 5e-4, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID3EtaN15N00", "-1.5 < #eta < 0.0, ID = 3;p_{T};", 0, 75, 5e-4, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID3EtaP00P15", "0.0 < #eta < 1.5, ID = 3;p_{T};", 0, 75, 5e-4, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID3EtaP15P25", "1.5 < #eta < 2.5, ID = 3;p_{T};", 0, 75, 5e-4, 1, true);
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID3PT05", "ID = 3, PT > 0.5");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID3PT1", "ID = 3, PT > 1.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID3PT2", "ID = 3, PT > 2.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID3PT5", "ID = 3, PT > 5.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID3PT10", "ID = 3, PT > 10.0");
   Add1DPlot(PdfFile, F1, F2, "HPFPTID4EtaN25N15", "-2.5 < #eta < -1.5, ID = 4;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID4EtaN15N00", "-1.5 < #eta < 0.0, ID = 4;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID4EtaP00P15", "0.0 < #eta < 1.5, ID = 4;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID4EtaP15P25", "1.5 < #eta < 2.5, ID = 4;p_{T};", 0, 75, 1e-6, 1, true);
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID4PT05", "ID = 4, PT > 0.5");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID4PT1", "ID = 4, PT > 1.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID4PT2", "ID = 4, PT > 2.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID4PT5", "ID = 4, PT > 5.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID4PT10", "ID = 4, PT > 10.0");
   Add1DPlot(PdfFile, F1, F2, "HPFPTID5EtaN25N15", "-2.5 < #eta < -1.5, ID = 5;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID5EtaN15N00", "-1.5 < #eta < 0.0, ID = 5;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID5EtaP00P15", "0.0 < #eta < 1.5, ID = 5;p_{T};", 0, 75, 1e-6, 1, true);
   Add1DPlot(PdfFile, F1, F2, "HPFPTID5EtaP15P25", "1.5 < #eta < 2.5, ID = 5;p_{T};", 0, 75, 1e-6, 1, true);
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID5PT05", "ID = 5, PT > 0.5");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID5PT1", "ID = 5, PT > 1.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID5PT2", "ID = 5, PT > 2.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID5PT5", "ID = 5, PT > 5.0");
   Add2DPlot(PdfFile, F1, F2, "HPFEtaPhiID5PT10", "ID = 5, PT > 10.0");

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Add1DPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName,
   string Title, double XMin, double XMax, double YMin, double YMax, bool LogY, bool Normalize)
{
   TH1D *H1 = (TH1D *)F1.Get(HName.c_str());
   TH1D *H2 = (TH1D *)F2.Get(HName.c_str());

   if(H1 == nullptr || H2 == nullptr)
   {
      PdfFile.AddTextPage("Histogram " + HName + " not found!");
      return;
   }

   if(Normalize == true)
   {
      H1->Scale(1 / H1->Integral());
      H2->Scale(1 / H2->Integral());
   }

   H2->SetMarkerStyle(20);
   H2->SetLineColor(kBlue);
   H2->SetMarkerColor(kBlue);
   H1->SetMarkerStyle(20);
   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   H1->Draw("same");
   H1->Draw("hist same");
   H2->Draw("same");
   H2->Draw("hist same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.91, "#color[2]{Target} #color[4]{Reference}");

   Canvas.SetLogy(LogY);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldRatio("HWorldRatio", Title.c_str(), 100, XMin, XMax, 100, 0.00, 2.00);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetYaxis()->SetTitle("Ratio");

   HWorldRatio.Draw("axis");

   int N = H1->GetNbinsX();
   TH1D HRatio("HRatio", Title.c_str(), N, XMin, XMax);
   HRatio.Divide(H1, H2);
   HRatio.Draw("same");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);
   GLine.Draw("l");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
}

void Add1DProfilePlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName,
   string Title, double XMin, double XMax, double YMin, double YMax, bool LogY)
{
   TProfile *H1 = (TProfile *)F1.Get(HName.c_str());
   TProfile *H2 = (TProfile *)F2.Get(HName.c_str());

   if(H1 == nullptr || H2 == nullptr)
   {
      PdfFile.AddTextPage("Histogram " + HName + " not found!");
      return;
   }

   H2->SetMarkerStyle(20);
   H2->SetLineColor(kBlue);
   H2->SetMarkerColor(kBlue);
   H1->SetMarkerStyle(20);
   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);

   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   H1->Draw("same");
   H1->Draw("hist same");
   H2->Draw("same");
   H2->Draw("hist same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.91, "#color[2]{Target} #color[4]{Reference}");

   Canvas.SetLogy(LogY);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldRatio("HWorldRatio", Title.c_str(), 100, XMin, XMax, 100, 0.00, 2.00);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetYaxis()->SetTitle("Ratio");

   HWorldRatio.Draw("axis");

   int N = H1->GetNbinsX();
   TH1D HRatio("HRatio", Title.c_str(), N, XMin, XMax);
   HRatio.Divide(H1, H2);
   HRatio.Draw("same");

   TGraph GLine;
   GLine.SetPoint(0, XMin, 1);
   GLine.SetPoint(1, XMax, 1);
   GLine.Draw("l");

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
}

void Add2DPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string HName, string Title, bool LogZ, bool Normalize)
{
   TH2D *H1 = (TH2D *)F1.Get(HName.c_str());
   TH2D *H2 = (TH2D *)F2.Get(HName.c_str());

   if(H1 == nullptr || H2 == nullptr)
   {
      PdfFile.AddTextPage("Histogram " + HName + " not found!");
      return;
   }

   if(Normalize == true)
   {
      H1->Scale(1 / H1->Integral());
      H2->Scale(1 / H2->Integral());
   }

   H1->SetStats(0);
   H2->SetStats(0);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   
   TCanvas Canvas;
   Canvas.Divide(2);
   Latex.SetTextAlign(22);
   Latex.SetTextSize(0.04);
   Latex.DrawLatex(0.50, 0.95, Title.c_str());
   
   Canvas.cd(1);
   H2->Draw("colz same");
   Latex.SetTextAlign(12);
   Latex.SetTextSize(0.03);
   Latex.DrawLatex(0.10, 0.91, "#color[4]{Reference}");
   Canvas.cd(2);
   H1->Draw("colz same");
   Latex.SetTextAlign(12);
   Latex.SetTextSize(0.03);
   Latex.DrawLatex(0.10, 0.91, "#color[2]{Target}");

   PdfFile.AddCanvas(Canvas);
}




