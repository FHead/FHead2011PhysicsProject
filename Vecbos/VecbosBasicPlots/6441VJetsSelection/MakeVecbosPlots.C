#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper.h"

void MakeVecbosPlots(string RootFile, string OutputBase = "Vecbos");
void PlotJetEnergyCorrectionPlots(TFile &F, PsFileHelper &PsFile, string HistogramName, string OutputBase);
void PlotCaloJetEnergyCorrectionFactorPlots(TFile &F, PsFileHelper &PsFile);
void MakeJetCountingHistograms(TFile &F, PsFileHelper &PsFile, string HistogramPrefix);
void SaveToFile(TFile &F, string HistogramName, string Option = "", bool LogY = false, bool LogZ = false,
   string OutputBase = "");

void MakeVecbosPlots(string RootFile, string OutputBase)
{
   // in-/out- put files
   PsFileHelper PsFile((OutputBase + ".ps").c_str());
   // PsFileHelper PsFileEnergyScale((OutputBase + "_EnergyScale.ps").c_str());
   TFile F(RootFile.c_str());

   // title page
   PsFile.AddTextPage("Vecbos plots, Yi Chen");
   // PsFileEnergyScale.AddTextPage("Vecbos plots for jet energy scale uncertainties");

   // MC plots
   PsFile.AddTextPage("MC Plots");

   PsFile.AddHistogramFromFile(F, "HMCZMass", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt1CaloJet", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt2CaloJet", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt3CaloJet", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt4CaloJet", "hist", true);
   PsFile.AddHistogramFromFile(F, "HMCZPt5CaloJet", "hist", true);

   // preselection plots
   PsFile.AddTextPage("Preselection Plots");

   PsFile.AddHistogramFromFile(F, "HNMuon", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNGlobalMuon", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNGlobalMuon10GeV", "text0 h", true);

   // muon distributions
   PsFile.AddTextPage("Muon Candidate plots");

   PsFile.AddHistogramFromFile(F, "HGlobalMuonPT", "", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonEta10GeV", "", false);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonPhi10GeV", "", false);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonDxy10GeV", "", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonIsolation10GeV", "", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonRelativeCombinedIsolation10GeV", "", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonChi210GeV", "", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonPixelHit10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonSiStripHit10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonTrackerHit10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HGlobalMuonValidMuonHit10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HPassMuonIDEta10GeV", "", false);
   PsFile.AddHistogramFromFile(F, "HPassMuonIDPhi10GeV", "", false);
   PsFile.AddHistogramFromFile(F, "HPassMuonIDPT10GeV", "", true);
   PsFile.AddHistogramFromFile(F, "HNGlobalMuonWithPixel10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNGlobalMuonWithTracker10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNGlobalMuonWithAllHits10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNPassMuonID10GeV", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNPassMuonIDFirstLeg", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HNPassMuonIDSecondLeg", "text0 h", true);

   PsFile.AddHistogramFromFile(F, "HDiMuonMass", "", true);
   PsFile.AddHistogramFromFile(F, "HDiGlobalMuonMass", "", true, false, false, true);
   PsFile.AddHistogramFromFile(F, "HDiGlobalOppositeMuonMass", "", true, false, false, true);
   PsFile.AddHistogramFromFile(F, "HDiGlobalSameMuonMass", "", true, false, false, true);

   // Z distributions
   PsFile.AddTextPage("Z Candidate Plots");

   PsFile.AddHistogramFromFile(F, "HNZCandidate2Global", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HZEta", "", true);
   PsFile.AddHistogramFromFile(F, "HZPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HZPt", "", true);
   PsFile.AddHistogramFromFile(F, "HZMass", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZEta", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZPt", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPt1CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPt2CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPt3CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPt4CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZPt5CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZMass", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZFirstLegEta", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZFirstLegPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZFirstLegPt", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZSecondLegEta", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZSecondLegPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZSecondLegPt", "", true);
   PsFile.AddHistogramFromFile(F, "HHighZDiMuonAngle", "", false);
   PsFile.AddHistogramFromFile(F, "HHighZMomentumVsDiMuonAngle", "colz", false);
   PsFile.AddHistogramFromFile(F, "HHighZMassVsLeadingMuonPT", "colz", false);
   PsFile.AddHistogramFromFile(F, "HighZDiMuonDPhi", "", true);

   TCanvas Canvas;
   TH1D *HZMass = (TH1D *)F.Get("HZMass");
   HZMass->SetStats(0);
   HZMass->SetTitle("Z Candidate Mass Spectrum");
   HZMass->GetXaxis()->SetRangeUser(60, 118);
   HZMass->GetXaxis()->SetTitle("Dimuon mass");
   HZMass->Draw();
   Canvas.SetLogy();
   Canvas.SaveAs((OutputBase + "_HZMass.png").c_str());
   Canvas.SaveAs((OutputBase + "_HZMass.eps").c_str());
   Canvas.SaveAs((OutputBase + "_HZMass.C").c_str());

   // calo jet distributions
   PsFile.AddTextPage("CaloJet Plots");
   // PsFileEnergyScale.AddTextPage("CaloJet Plots");

   PsFile.AddHistogramFromFile(F, "HNCaloJet", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HCaloJetPt", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJetLeadingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJetLeadingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetLeadingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetSinglePt", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJetSingleEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetSinglePhi", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetLeadingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetLeadingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetLeadingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetFollowingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetFollowingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJet2JetFollowingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetTotalPTVsLeadingZPT", "colz", false);
   PsFile.AddHistogramFromFile(F, "HCaloJetTotalPT", "", true);

   PsFile.AddHistogramFromFile(F, "HCaloJetCorrectionCountVsType", "text0 colz", false);

   PlotJetEnergyCorrectionPlots(F, PsFile, "HCaloJetCorrectionCountVsType", OutputBase);
   // PlotJetEnergyCorrectionPlots(F, PsFileEnergyScale, "HCaloJetCorrectionCountVsType", OutputBase);

   PlotCaloJetEnergyCorrectionFactorPlots(F, PsFile);

   // Uncorrected CaloJet distributions
   PsFile.AddTextPage("Uncorrected calojet plots");

   PsFile.AddHistogramFromFile(F, "HNUncorrectedCaloJet", "hist text0", true);
   PsFile.AddHistogramFromFile(F, "HUncorrectedCaloJetPt", "", true);
   PsFile.AddHistogramFromFile(F, "HUncorrectedCaloJetLeadingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HUncorrectedCaloJetLeadingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HUncorrectedCaloJetLeadingPhi", "", false);

   // PF jet distributions
   PsFile.AddTextPage("PFJet Plots");
   // PsFileEnergyScale.AddTextPage("PFJet Plots");

   PsFile.AddHistogramFromFile(F, "HNPFJet", "text0 h", true);
   PsFile.AddHistogramFromFile(F, "HPFJetPt", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJetLeadingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJetLeadingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetLeadingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetSinglePt", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJetSingleEta", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetSinglePhi", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetLeadingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetLeadingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetLeadingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetFollowingPt", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetFollowingEta", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJet2JetFollowingPhi", "", false);
   PsFile.AddHistogramFromFile(F, "HPFJetTotalPTVsLeadingZPT", "colz", false);
   PsFile.AddHistogramFromFile(F, "HPFJetTotalPT", "", true);

   PsFile.AddHistogramFromFile(F, "HPFJetClosestToFirstLegDEtaDPhi", "colz", false, true);
   PsFile.AddHistogramFromFile(F, "HPFJetClosestToSecondLegDEtaDPhi", "colz", false, true);

   PsFile.AddHistogramFromFile(F, "HPFJetClosestToFirstLegPTPT", "colz", false, true);
   PsFile.AddHistogramFromFile(F, "HPFJetClosestToSecondLegPTPT", "colz", false, true);

   PsFile.AddHistogramFromFile(F, "HPFJetClosestToFirstLegPTOverMuonPT", "", true);
   PsFile.AddHistogramFromFile(F, "HPFJetClosestToSecondLegPTOverMuonPT", "", true);

   SaveToFile(F, "HPFJetClosestToFirstLegDEtaDPhi", "colz", false, true, OutputBase);
   SaveToFile(F, "HPFJetClosestToSecondLegDEtaDPhi", "colz", false, true, OutputBase);

   SaveToFile(F, "HPFJetClosestToFirstLegPTPT", "colz", false, true, OutputBase);
   SaveToFile(F, "HPFJetClosestToSecondLegPTPT", "colz", false, true, OutputBase);
   
   SaveToFile(F, "HPFJetClosestToFirstLegPTOverMuonPT", "", true, false, OutputBase);
   SaveToFile(F, "HPFJetClosestToSecondLegPTOverMuonPT", "", true, false, OutputBase);

   PsFile.AddHistogramFromFile(F, "HPFJetCorrectionCountVsType", "text0 colz", false);

   PlotJetEnergyCorrectionPlots(F, PsFile, "HPFJetCorrectionCountVsType", OutputBase);
   // PlotJetEnergyCorrectionPlots(F, PsFileEnergyScale, "HPFJetCorrectionCountVsType", OutputBase);

   // track jet distributions
   PsFile.AddTextPage("TrackJet Plots - coming soon");

   // MET distributions
   PsFile.AddTextPage("MET/MHT Plots");

   PsFile.AddHistogramFromFile(F, "HLeadingZMassVsSinPhi", "colz", false);
   PsFile.AddHistogramFromFile(F, "HPhiMET", "", false);
   PsFile.AddHistogramFromFile(F, "HMET", "", true);
   PsFile.AddHistogramFromFile(F, "HMET1CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HMET2CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HMET3CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HMET4CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HMET5CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPhiPFMET", "", false);
   PsFile.AddHistogramFromFile(F, "HPFMET", "", true);
   PsFile.AddHistogramFromFile(F, "HPFMET1CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPFMET2CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPFMET3CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPFMET4CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPFMET5CaloJet", "", true);
   PsFile.AddHistogramFromFile(F, "HPhiMHTLeadingZ", "", false);
   PsFile.AddHistogramFromFile(F, "HMHTLeadingZ", "", true);
   PsFile.AddHistogramFromFile(F, "HSinPhiLeadingZ", "", false);

   // new phi variables
   PsFile.AddTextPage("Plots for new angular variable on 6153");

   PsFile.AddHistogramFromFile(F, "HLeadingZMassVsSinPhiPF", "colz", false);
   PsFile.AddHistogramFromFile(F, "HMuonCorrectedPFMETPhiLeadingZ", "", false);
   PsFile.AddHistogramFromFile(F, "HBoostedPFJetTransverseSphericityPhiLeadingZ", "", false);
   PsFile.AddHistogramFromFile(F, "HSinPhiPFLeadingZ", "", false);

   // Counting distributions
   PsFile.AddTextPage("Counting Events");

   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet0", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet1", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet2", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet3", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet4", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionCaloJet5", "text30 h", true);

   MakeJetCountingHistograms(F, PsFile, "CountEventsSelectionUncorrectedCaloJet");

   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet0", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet1", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet2", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet3", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet4", "text30 h", true);
   PsFile.AddHistogramFromFile(F, "CountEventsSelectionUncorrectedCaloJet5", "text30 h", true);

   MakeJetCountingHistograms(F, PsFile, "CountEventsSelectionCaloJet");

   PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet0", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet1", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet2", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet3", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet4", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionPFJet5", "text30 h", true);

   // MakeJetCountingHistograms(F, PsFile, "CountEventsSelectionPFJet");

   PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet0", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet1", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet2", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet3", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet4", "text30 h", true);
   // PsFile.AddHistogramFromFile(F, "CountEventsSelectionTrackJet5", "text30 h", true);

   // MakeJetCountingHistograms(F, PsFile, "CountEventsSelectionTrackJet");

   // final touch
   PsFile.AddTimeStampPage();
   // PsFileEnergyScale.AddTimeStampPage();

   // clean up
   F.Close();
   PsFile.Close();
   // PsFileEnergyScale.Close();
}

void PlotJetEnergyCorrectionPlots(TFile &F, PsFileHelper &PsFile, string HistogramName, string OutputBase)
{
   TH2D *HJetCorrectionCountVsType = (TH2D *)F.Get(HistogramName.c_str())->Clone("Yay");
   HJetCorrectionCountVsType->GetXaxis()->SetTitle("Inclusive jet count");
   for(int x = HJetCorrectionCountVsType->GetNbinsX(); x >= 0; x--)
   {
      for(int y = 1; y <= HJetCorrectionCountVsType->GetNbinsY(); y++)
      {
         double NextBin = HJetCorrectionCountVsType->GetBinContent(x + 1, y);
         double ThisBin = HJetCorrectionCountVsType->GetBinContent(x, y);
         HJetCorrectionCountVsType->SetBinContent(x, y, NextBin + ThisBin);
      }
   }
   PsFile.AddPlot(HJetCorrectionCountVsType, "text0 colz", false);

   TGraphAsymmErrors EtaScaleGraph;
   TGraphAsymmErrors AbsoluteScaleGraph;

   EtaScaleGraph.SetNameTitle("EtaScaleGraph", "Eta scale correction uncertainties");
   EtaScaleGraph.GetXaxis()->SetTitle("Inclusive jet multiplicities");
   EtaScaleGraph.GetYaxis()->SetTitle("Number of events in the sample");
   EtaScaleGraph.SetFillColor(6);

   AbsoluteScaleGraph.SetNameTitle("AbsoluteScaleGraph", "Absolute scale correction uncertainties");
   AbsoluteScaleGraph.GetXaxis()->SetTitle("Inclusive jet multiplicities");
   AbsoluteScaleGraph.GetYaxis()->SetTitle("Number of events in the sample");
   AbsoluteScaleGraph.SetFillColor(7);

   for(int x = 1; x <= HJetCorrectionCountVsType->GetNbinsX() && x <= 6; x++)
   {
      EtaScaleGraph.SetPoint(x - 1, x - 1, HJetCorrectionCountVsType->GetBinContent(x, 5));
      EtaScaleGraph.SetPointError(x - 1, 0, 0,
         HJetCorrectionCountVsType->GetBinContent(x, 5) - HJetCorrectionCountVsType->GetBinContent(x, 4),
         HJetCorrectionCountVsType->GetBinContent(x, 3) - HJetCorrectionCountVsType->GetBinContent(x, 5));
      AbsoluteScaleGraph.SetPoint(x - 1, x - 1, HJetCorrectionCountVsType->GetBinContent(x, 5));
      AbsoluteScaleGraph.SetPointError(x - 1, 0, 0,
         HJetCorrectionCountVsType->GetBinContent(x, 5) - HJetCorrectionCountVsType->GetBinContent(x, 2),
         HJetCorrectionCountVsType->GetBinContent(x, 1) - HJetCorrectionCountVsType->GetBinContent(x, 5));
   }

   // PsFile.AddPlot(EtaScaleGraph, "a3", true);
   // PsFile.AddPlot(AbsoluteScaleGraph, "a3", true);

   TCanvas Canvas("Canvas", "Canvas", 0, 0, 1024, 768);

   AbsoluteScaleGraph.SetTitle("Eta/absolute scale uncertainties, separate");

   AbsoluteScaleGraph.Draw("a3");
   EtaScaleGraph.Draw("3");

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillColor(0);
   legend.AddEntry(&AbsoluteScaleGraph, "Absolute scale", "f");
   legend.AddEntry(&EtaScaleGraph, "Eta-dependent scale", "f");
   legend.Draw();

   Canvas.SetLogy();

   Canvas.SaveAs(Form("%s_%s_JES.png", OutputBase.c_str(), HistogramName.c_str()));

   PsFile.AddCanvas(Canvas);

   HJetCorrectionCountVsType->SetTitle("Jet percentage change with different jet energy scale effects");
   for(int x = 1; x <= HJetCorrectionCountVsType->GetNbinsX(); x++)
   {
      double Denominator = HJetCorrectionCountVsType->GetBinContent(x, HJetCorrectionCountVsType->GetNbinsY());
      for(int y = 1; y <= HJetCorrectionCountVsType->GetNbinsY(); y++)
      {
         double Nominator = HJetCorrectionCountVsType->GetBinContent(x, y);
         HJetCorrectionCountVsType->SetBinContent(x, y, (double)(int)((Nominator / Denominator - 1) * 10000) / 100);
      }
   }
   PsFile.AddPlot(HJetCorrectionCountVsType, "text0 colz", false);
}

void PlotCaloJetEnergyCorrectionFactorPlots(TFile &F, PsFileHelper &PsFile)
{
   // Energy correction factors!
   TH2D *HCaloJetCorrectionFactorSum = (TH2D *)F.Get("HCaloJetCorrectionFactorSum");
   TH2D *HCaloJetCorrectionFactorSum2 = (TH2D *)F.Get("HCaloJetCorrectionFactorSum2");
   TH2D *HCaloJetCorrectionFactorCount = (TH2D *)F.Get("HCaloJetCorrectionFactorCount");

   TH2D *HCaloJetCorrectionFactorMean = (TH2D *)F.Get("HCaloJetCorrectionFactorMean");
   TH2D *HCaloJetCorrectionFactorRMS = (TH2D *)F.Get("HCaloJetCorrectionFactorRMS");

   if(HCaloJetCorrectionFactorSum == NULL)
      return;
   if(HCaloJetCorrectionFactorSum2 == NULL)
      return;
   if(HCaloJetCorrectionFactorCount == NULL)
      return;
   if(HCaloJetCorrectionFactorMean == NULL)
      return;
   if(HCaloJetCorrectionFactorRMS == NULL)
      return;

   HCaloJetCorrectionFactorMean->SetStats(0);
   HCaloJetCorrectionFactorRMS->SetStats(0);

   int NBinsX = HCaloJetCorrectionFactorCount->GetNbinsX();
   int NBinsY = HCaloJetCorrectionFactorCount->GetNbinsY();

   for(int i = 1; i <= NBinsX; i++)
   {
      for(int j = 1; j <= NBinsY; j++)
      {
         double Sum = HCaloJetCorrectionFactorSum->GetBinContent(i, j);
         double Sum2 = HCaloJetCorrectionFactorSum2->GetBinContent(i, j);
         double Count = HCaloJetCorrectionFactorCount->GetBinContent(i, j);

         if(Count < 1e-3)
            continue;

         HCaloJetCorrectionFactorMean->SetBinContent(i, j, Sum / Count);
         HCaloJetCorrectionFactorRMS->SetBinContent(i, j, sqrt((Sum2 - Sum * Sum / Count) / Count));
      }
   }

   HCaloJetCorrectionFactorMean->SetMaximum(4);
   HCaloJetCorrectionFactorRMS->SetMaximum(1);

   PsFile.AddPlot(HCaloJetCorrectionFactorCount, "colz", false, true);
   PsFile.AddPlot(HCaloJetCorrectionFactorMean, "colz", false, false);
   PsFile.AddPlot(HCaloJetCorrectionFactorRMS, "colz", false, false);
}

void MakeJetCountingHistograms(TFile &F, PsFileHelper &PsFile, string HistogramPrefix)
{
   TH2D FinalHistogram(Form("%sFinalHistogram", HistogramPrefix.c_str()),
      Form("%s efficiency for different inclusive jet bins", HistogramPrefix.c_str()),
      18, -0.5, 17.5, 9, -0.5, 8.5);

   for(int i = 0; i <= 5; i++)   // jet count
   {
      FinalHistogram.GetXaxis()->SetBinLabel(i * 3 + 1, Form("Count, %d jet", i));
      FinalHistogram.GetXaxis()->SetBinLabel(i * 3 + 2, Form("Relative, %d jet", i));
      FinalHistogram.GetXaxis()->SetBinLabel(i * 3 + 3, Form("Cumulative, %d jet", i));
   }

   FinalHistogram.GetYaxis()->SetBinLabel(9, "All");
   FinalHistogram.GetYaxis()->SetBinLabel(8, "Two reco muons");
   FinalHistogram.GetYaxis()->SetBinLabel(7, "Two global muons");
   FinalHistogram.GetYaxis()->SetBinLabel(6, "Pixel hit");
   FinalHistogram.GetYaxis()->SetBinLabel(5, "Tracking hit");
   FinalHistogram.GetYaxis()->SetBinLabel(4, "Muon hit");
   FinalHistogram.GetYaxis()->SetBinLabel(3, "Chi2");
   FinalHistogram.GetYaxis()->SetBinLabel(2, "Isolation");
   FinalHistogram.GetYaxis()->SetBinLabel(1, "Kinematics");

   map<int, int> IndexMap;
   IndexMap[1] = 9;
   IndexMap[3] = 8;
   IndexMap[4] = 7;
   IndexMap[5] = 6;
   IndexMap[6] = 5;
   IndexMap[7] = 4;
   IndexMap[8] = 3;
   IndexMap[9] = 2;
   IndexMap[10] = 1;

   for(int i = 0; i <= 5; i++)   // jet count again
   {
      TH1D *Histogram = (TH1D *)F.Get(Form("%s%d", HistogramPrefix.c_str(), i));

      double Values[9] = {0};
      int Count = 0;
      for(int j = 1; j <= 9; j++)
      {
         if(j == 2)   // HLT
            continue;

         Values[Count] = Histogram->GetBinContent(j);
         Count = Count + 1;
      }

      for(int j = 0; j < 9; j++)
      {
         FinalHistogram.SetBinContent(i * 3 + 1, 9 - j, Values[j]);

         if(j != 0)
         {
            FinalHistogram.SetBinContent(i * 3 + 2, 9 - j, Values[j] / Values[j-1]);
            FinalHistogram.SetBinContent(i * 3 + 3, 9 - j, Values[j] / Values[0]);
         }
      }
   }

   FinalHistogram.SetStats(0);
   FinalHistogram.SetMarkerSize(1.25);

   TCanvas canvas("C1", "C2", 0, 0, 1024, 600);

   FinalHistogram.Draw("text42");

   PsFile.AddCanvas(canvas);
}

void SaveToFile(TFile &F, string HistogramName, string Option, bool LogY, bool LogZ, string OutputBase)
{
   TH1 *Histogram = (TH1 *)F.Get(HistogramName.c_str());

   if(Histogram == NULL)
      return;

   TCanvas canvas("C", "C", 0, 0, 1024, 768);

   Histogram->Draw(Option.c_str());

   if(LogY == true)
      canvas.SetLogy();
   if(LogZ == true)
      canvas.SetLogz();

   canvas.SaveAs((OutputBase + "_" + HistogramName + ".eps").c_str());
   canvas.SaveAs((OutputBase + "_" + HistogramName + ".png").c_str());
   canvas.SaveAs((OutputBase + "_" + HistogramName + ".C").c_str());

   gROOT->ProcessLine((".! epstopdf " + OutputBase + "_" + HistogramName + ".eps").c_str());
}

