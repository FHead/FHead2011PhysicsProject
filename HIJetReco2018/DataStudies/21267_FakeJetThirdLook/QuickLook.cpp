#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

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

#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "Messenger.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputFileName         = CL.Get("Output", "Result.root");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   vector<double> MVACut = {0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.00};
   vector<string> MVALabel = {"MVA090", "MVA091", "MVA092", "MVA093", "MVA094", "MVA095", "MVA096", "MVA097", "MVA098", "MVA099", "MVA100"};
   // vector<double> MVACut = {0.90, 0.95, 0.98, 1.00};
   // vector<string> MVALabel = {"MVA090", "MVA095", "MVA098", "MVA100"};

   TH1D HN("HN", "", 1, 0, 1);
   
   vector<TH1D *> HJetCount(MVALabel.size());
   vector<TH1D *> HJetCountPT30(MVALabel.size());
   vector<TH1D *> HJetCountPT50(MVALabel.size());
   vector<TH1D *> HJetCountPT75(MVALabel.size());
   vector<TH1D *> HJetCountPT100(MVALabel.size());
   vector<TH1D *> HJetCountPT125(MVALabel.size());
   vector<TH1D *> HJetPT(MVALabel.size());
   vector<TH1D *> HLeadingJetPT(MVALabel.size());
   vector<TH1D *> HJetPTEtaN25N15(MVALabel.size());
   vector<TH1D *> HJetPTEtaN15N00(MVALabel.size());
   vector<TH1D *> HJetPTEtaP00P15(MVALabel.size());
   vector<TH1D *> HJetPTEtaP15P25(MVALabel.size());
   vector<TH2D *> HJetEtaPhiPT30(MVALabel.size());
   vector<TH2D *> HJetEtaPhiPT50(MVALabel.size());
   vector<TH2D *> HJetEtaPhiPT75(MVALabel.size());
   vector<TH2D *> HJetEtaPhiPT100(MVALabel.size());
   vector<TH2D *> HJetEtaPhiPT125(MVALabel.size());
   vector<TH1D *> HTrackMETX(MVALabel.size());
   vector<TH1D *> HTrackMETY(MVALabel.size());
   vector<TH1D *> HTrackMET(MVALabel.size());
   vector<TH1D *> HPositiveTrackMETX(MVALabel.size());
   vector<TH1D *> HPositiveTrackMETY(MVALabel.size());
   vector<TH1D *> HPositiveTrackMET(MVALabel.size());
   vector<TH1D *> HTrackMETXPeripheral(MVALabel.size());
   vector<TH1D *> HTrackMETYPeripheral(MVALabel.size());
   vector<TH1D *> HTrackMETPeripheral(MVALabel.size());
   vector<TH1D *> HPositiveTrackMETXPeripheral(MVALabel.size());
   vector<TH1D *> HPositiveTrackMETYPeripheral(MVALabel.size());
   vector<TH1D *> HPositiveTrackMETPeripheral(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID2PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID2PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID2PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID2PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID4PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID4PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID4PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID4PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID5PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID5PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID5PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID5PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID6PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID6PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID6PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID6PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID7PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID7PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID7PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID7PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID22PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID22PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID22PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID22PT10(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID23PT1(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID23PT2(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID23PT5(MVALabel.size());
   vector<TH2D *> HTrackEtaPhiID23PT10(MVALabel.size());

   for(int iM = 0; iM < (int)MVALabel.size(); iM++)
   {
      HJetCount[iM] = new TH1D(Form("HJetCount%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetCountPT30[iM] = new TH1D(Form("HJetCountPT30%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetCountPT50[iM] = new TH1D(Form("HJetCountPT50%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetCountPT75[iM] = new TH1D(Form("HJetCountPT75%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetCountPT100[iM] = new TH1D(Form("HJetCountPT100%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetCountPT125[iM] = new TH1D(Form("HJetCountPT125%s", MVALabel[iM].c_str()), ";Jet count;", 100, 0, 100);
      HJetPT[iM] = new TH1D(Form("HJetPT%s", MVALabel[iM].c_str()), ";Jet p_{T};", 100, 0, 400);
      HLeadingJetPT[iM] = new TH1D(Form("HLeadingJetPT%s", MVALabel[iM].c_str()), ";Leading jet p_{T};", 100, 0, 400);
      HJetPTEtaN25N15[iM] = new TH1D(Form("HJetPTEtaN25N15%s", MVALabel[iM].c_str()), "-2.5 < #eta < -1.5;Jet p_{T};", 100, 0, 400);
      HJetPTEtaN15N00[iM] = new TH1D(Form("HJetPTEtaN15N00%s", MVALabel[iM].c_str()), "-1.5 < #eta < 0.0;Jet p_{T};", 100, 0, 400);
      HJetPTEtaP00P15[iM] = new TH1D(Form("HJetPTEtaP00P15%s", MVALabel[iM].c_str()), "0.0 < #eta < 1.5;Jet p_{T};", 100, 0, 400);
      HJetPTEtaP15P25[iM] = new TH1D(Form("HJetPTEtaP15P25%s", MVALabel[iM].c_str()), "1.5 < #eta < 2.5;Jet p_{T};", 100, 0, 400);
      HJetEtaPhiPT30[iM] = new TH2D(Form("HJetEtaPhiPT30%s", MVALabel[iM].c_str()), "Jet p_{T} > 30;Jet #eta;Jet #phi", 75, -2.5, 2.5, 75, -M_PI, M_PI);
      HJetEtaPhiPT50[iM] = new TH2D(Form("HJetEtaPhiPT50%s", MVALabel[iM].c_str()), "Jet p_{T} > 50;Jet #eta;Jet #phi", 75, -2.5, 2.5, 75, -M_PI, M_PI);
      HJetEtaPhiPT75[iM] = new TH2D(Form("HJetEtaPhiPT75%s", MVALabel[iM].c_str()), "Jet p_{T} > 75;Jet #eta;Jet #phi", 75, -2.5, 2.5, 75, -M_PI, M_PI);
      HJetEtaPhiPT100[iM] = new TH2D(Form("HJetEtaPhiPT100%s", MVALabel[iM].c_str()), "Jet p_{T} > 100;Jet #eta;Jet #phi", 75, -2.5, 2.5, 75, -M_PI, M_PI);
      HJetEtaPhiPT125[iM] = new TH2D(Form("HJetEtaPhiPT125%s", MVALabel[iM].c_str()), "Jet p_{T} > 125;Jet #eta;Jet #phi", 75, -2.5, 2.5, 75, -M_PI, M_PI);
      HTrackMETX[iM] = new TH1D(Form("HTrackMETX%s", MVALabel[iM].c_str()), ";MET(x);", 150, -500, 500);
      HTrackMETY[iM] = new TH1D(Form("HTrackMETY%s", MVALabel[iM].c_str()), ";MET(y);", 150, -500, 500);
      HTrackMET[iM] = new TH1D(Form("HTrackMET%s", MVALabel[iM].c_str()), ";MET;", 150, 0, 700);
      HPositiveTrackMETX[iM] = new TH1D(Form("HPositiveTrackMETX%s", MVALabel[iM].c_str()), ";MET(x);", 150, -500, 500);
      HPositiveTrackMETY[iM] = new TH1D(Form("HPositiveTrackMETY%s", MVALabel[iM].c_str()), ";MET(y);", 150, -500, 500);
      HPositiveTrackMET[iM] = new TH1D(Form("HPositiveTrackMET%s", MVALabel[iM].c_str()), ";MET;", 150, 0, 700);
      HTrackMETXPeripheral[iM] = new TH1D(Form("HTrackMETXPeripheral%s", MVALabel[iM].c_str()), ";MET(x);", 150, -100, 100);
      HTrackMETYPeripheral[iM] = new TH1D(Form("HTrackMETYPeripheral%s", MVALabel[iM].c_str()), ";MET(y);", 150, -100, 100);
      HTrackMETPeripheral[iM] = new TH1D(Form("HTrackMETPeripheral%s", MVALabel[iM].c_str()), ";MET;", 150, 0, 100);
      HPositiveTrackMETXPeripheral[iM] = new TH1D(Form("HPositiveTrackMETXPeripheral%s", MVALabel[iM].c_str()), ";MET(x);", 150, -100, 100);
      HPositiveTrackMETYPeripheral[iM] = new TH1D(Form("HPositiveTrackMETYPeripheral%s", MVALabel[iM].c_str()), ";MET(y);", 150, -100, 100);
      HPositiveTrackMETPeripheral[iM] = new TH1D(Form("HPositiveTrackMETPeripheral%s", MVALabel[iM].c_str()), ";MET;", 150, 0, 100);
      HTrackEtaPhiID2PT1[iM] = new TH2D(Form("HTrackEtaPhiID2PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 2;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID2PT2[iM] = new TH2D(Form("HTrackEtaPhiID2PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 2;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID2PT5[iM] = new TH2D(Form("HTrackEtaPhiID2PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 2;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID2PT10[iM] = new TH2D(Form("HTrackEtaPhiID2PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 2;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID4PT1[iM] = new TH2D(Form("HTrackEtaPhiID4PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 4;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID4PT2[iM] = new TH2D(Form("HTrackEtaPhiID4PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 4;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID4PT5[iM] = new TH2D(Form("HTrackEtaPhiID4PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 4;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID4PT10[iM] = new TH2D(Form("HTrackEtaPhiID4PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 4;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID5PT1[iM] = new TH2D(Form("HTrackEtaPhiID5PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID5PT2[iM] = new TH2D(Form("HTrackEtaPhiID5PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID5PT5[iM] = new TH2D(Form("HTrackEtaPhiID5PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID5PT10[iM] = new TH2D(Form("HTrackEtaPhiID5PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 5;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID6PT1[iM] = new TH2D(Form("HTrackEtaPhiID6PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 6;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID6PT2[iM] = new TH2D(Form("HTrackEtaPhiID6PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 6;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID6PT5[iM] = new TH2D(Form("HTrackEtaPhiID6PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 6;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID6PT10[iM] = new TH2D(Form("HTrackEtaPhiID6PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 6;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID7PT1[iM] = new TH2D(Form("HTrackEtaPhiID7PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 7;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID7PT2[iM] = new TH2D(Form("HTrackEtaPhiID7PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 7;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID7PT5[iM] = new TH2D(Form("HTrackEtaPhiID7PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 7;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID7PT10[iM] = new TH2D(Form("HTrackEtaPhiID7PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 7;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID22PT1[iM] = new TH2D(Form("HTrackEtaPhiID22PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 22;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID22PT2[iM] = new TH2D(Form("HTrackEtaPhiID22PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 22;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID22PT5[iM] = new TH2D(Form("HTrackEtaPhiID22PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 22;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID22PT10[iM] = new TH2D(Form("HTrackEtaPhiID22PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 22;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID23PT1[iM] = new TH2D(Form("HTrackEtaPhiID23PT1%s", MVALabel[iM].c_str()), "PT > 1, ID = 23;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID23PT2[iM] = new TH2D(Form("HTrackEtaPhiID23PT2%s", MVALabel[iM].c_str()), "PT > 2, ID = 23;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID23PT5[iM] = new TH2D(Form("HTrackEtaPhiID23PT5%s", MVALabel[iM].c_str()), "PT > 5, ID = 23;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
      HTrackEtaPhiID23PT10[iM] = new TH2D(Form("HTrackEtaPhiID23PT10%s", MVALabel[iM].c_str()), "PT > 10, ID = 23;eta;phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   }

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MHiEvent(InputFile);
      TriggerTreeMessenger MHLT(InputFile);
      TrackTreeMessenger MTrack(InputFile);

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
         MHLT.GetEntry(iE);
         MTrack.GetEntry(iE);

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

         for(int iM = 0; iM < (int)MVACut.size(); iM++)
         {
            vector<PseudoJet> Tracks;
            FourVector TrackMET;
            FourVector PositiveTrackMET;

            for(int iT = 0; iT < MTrack.TrackCount; iT++)
            {
               if(MTrack.HighPurity[iT] == false)
                  continue;
               if(MTrack.TrackAlgo[iT] == 6 && MTrack.TrackMVA[iT] < MVACut[iM])
                  continue;

               if(MTrack.TrackAlgo[iT] == 2)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID2PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID2PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID2PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID2PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 4)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID4PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID4PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID4PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID4PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 5)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID5PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID5PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID5PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID5PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 6)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID6PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID6PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID6PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID6PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 7)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID7PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID7PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID7PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID7PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 22)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID22PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID22PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID22PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID22PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
               if(MTrack.TrackAlgo[iT] == 23)
               {
                  if(MTrack.TrackPT[iT] > 1)    HTrackEtaPhiID23PT1[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 2)    HTrackEtaPhiID23PT2[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 5)    HTrackEtaPhiID23PT5[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
                  if(MTrack.TrackPT[iT] > 10)   HTrackEtaPhiID23PT10[iM]->Fill(MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               }
            }

            for(int iT = 0; iT < MTrack.TrackCount; iT++)
            {
               if(MTrack.HighPurity[iT] == false)
                  continue;
               if(MTrack.TrackAlgo[iT] == 6 && MTrack.TrackMVA[iT] < MVACut[iM])
                  continue;

               FourVector P;
               P.SetPtEtaPhi(MTrack.TrackPT[iT], MTrack.TrackEta[iT], MTrack.TrackPhi[iT]);
               Tracks.push_back(PseudoJet(P[1], P[2], P[3], P[0]));

               TrackMET = TrackMET - P;
               if(P[3] > 0)
                  PositiveTrackMET = TrackMET - P;
            }
            JetDefinition Definition(antikt_algorithm, 0.4);
            ClusterSequence Sequence(Tracks, Definition);
            vector<PseudoJet> FastJets = Sequence.inclusive_jets();

            HTrackMETX[iM]->Fill((TrackMET[1] + TrackMET[2]) / sqrt(2));
            HTrackMETY[iM]->Fill((TrackMET[2] - TrackMET[1]) / sqrt(2));
            HTrackMET[iM]->Fill(TrackMET.GetPT());
            HPositiveTrackMETX[iM]->Fill((PositiveTrackMET[1] + PositiveTrackMET[2]) / sqrt(2));
            HPositiveTrackMETY[iM]->Fill((PositiveTrackMET[2] - PositiveTrackMET[1]) / sqrt(2));
            HPositiveTrackMET[iM]->Fill(PositiveTrackMET.GetPT());
            if(MHiEvent.hiBin > 100)
            {
               HTrackMETXPeripheral[iM]->Fill((TrackMET[1] + TrackMET[2]) / sqrt(2));
               HTrackMETYPeripheral[iM]->Fill((TrackMET[2] - TrackMET[1]) / sqrt(2));
               HTrackMETPeripheral[iM]->Fill(TrackMET.GetPT());
               HPositiveTrackMETXPeripheral[iM]->Fill((PositiveTrackMET[1] + PositiveTrackMET[2]) / sqrt(2));
               HPositiveTrackMETYPeripheral[iM]->Fill((PositiveTrackMET[2] - PositiveTrackMET[1]) / sqrt(2));
               HPositiveTrackMETPeripheral[iM]->Fill(PositiveTrackMET.GetPT());
            }

            vector<FourVector> Jets;
            for(PseudoJet J : FastJets)
               Jets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));

            int JetCount = 0;
            int JetCountPT30 = 0;
            int JetCountPT50 = 0;
            int JetCountPT75 = 0;
            int JetCountPT100 = 0;
            int JetCountPT125 = 0;

            if(Jets.size() > 0)
               HLeadingJetPT[iM]->Fill(Jets[0].GetPT());
            for(FourVector J : Jets)
            {
               JetCount = JetCount + 1;
               if(J.GetPT() > 30)    JetCountPT30 = JetCountPT30 + 1;
               if(J.GetPT() > 50)    JetCountPT50 = JetCountPT50 + 1;
               if(J.GetPT() > 75)    JetCountPT75 = JetCountPT75 + 1;
               if(J.GetPT() > 100)   JetCountPT100 = JetCountPT100 + 1;
               if(J.GetPT() > 125)   JetCountPT125 = JetCountPT125 + 1;

               HJetPT[iM]->Fill(J.GetPT());
               if(J.GetEta() > -2.5 && J.GetEta() < -1.5)
                  HJetPTEtaN25N15[iM]->Fill(J.GetPT());
               if(J.GetEta() > -1.5 && J.GetEta() < 0.0)
                  HJetPTEtaN15N00[iM]->Fill(J.GetPT());
               if(J.GetEta() > 0.0 && J.GetEta() < 1.5)
                  HJetPTEtaP00P15[iM]->Fill(J.GetPT());
               if(J.GetEta() > 1.5 && J.GetEta() < 2.5)
                  HJetPTEtaP15P25[iM]->Fill(J.GetPT());

               if(J.GetPT() > 30)
                  HJetEtaPhiPT30[iM]->Fill(J.GetEta(), J.GetPhi());
               if(J.GetPT() > 50)
                  HJetEtaPhiPT50[iM]->Fill(J.GetEta(), J.GetPhi());
               if(J.GetPT() > 75)
                  HJetEtaPhiPT75[iM]->Fill(J.GetEta(), J.GetPhi());
               if(J.GetPT() > 100)
                  HJetEtaPhiPT100[iM]->Fill(J.GetEta(), J.GetPhi());
               if(J.GetPT() > 125)
                  HJetEtaPhiPT125[iM]->Fill(J.GetEta(), J.GetPhi());
            }

            HJetCount[iM]->Fill(JetCount);
            HJetCountPT30[iM]->Fill(JetCountPT30);
            HJetCountPT50[iM]->Fill(JetCountPT50);
            HJetCountPT75[iM]->Fill(JetCountPT75);
            HJetCountPT100[iM]->Fill(JetCountPT100);
            HJetCountPT125[iM]->Fill(JetCountPT125);
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();

   HN.Write();
   
   for(auto H : HJetCount)                      if(H != nullptr)   H->Write();
   for(auto H : HJetCountPT30)                  if(H != nullptr)   H->Write();
   for(auto H : HJetCountPT50)                  if(H != nullptr)   H->Write();
   for(auto H : HJetCountPT75)                  if(H != nullptr)   H->Write();
   for(auto H : HJetCountPT100)                 if(H != nullptr)   H->Write();
   for(auto H : HJetCountPT125)                 if(H != nullptr)   H->Write();
   for(auto H : HJetPT)                         if(H != nullptr)   H->Write();
   for(auto H : HLeadingJetPT)                  if(H != nullptr)   H->Write();
   for(auto H : HJetPTEtaN25N15)                if(H != nullptr)   H->Write();
   for(auto H : HJetPTEtaN15N00)                if(H != nullptr)   H->Write();
   for(auto H : HJetPTEtaP00P15)                if(H != nullptr)   H->Write();
   for(auto H : HJetPTEtaP15P25)                if(H != nullptr)   H->Write();
   for(auto H : HJetEtaPhiPT30)                 if(H != nullptr)   H->Write();
   for(auto H : HJetEtaPhiPT50)                 if(H != nullptr)   H->Write();
   for(auto H : HJetEtaPhiPT75)                 if(H != nullptr)   H->Write();
   for(auto H : HJetEtaPhiPT100)                if(H != nullptr)   H->Write();
   for(auto H : HJetEtaPhiPT125)                if(H != nullptr)   H->Write();
   for(auto H : HTrackMETX)                     if(H != nullptr)   H->Write();
   for(auto H : HTrackMETY)                     if(H != nullptr)   H->Write();
   for(auto H : HTrackMET)                      if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMETX)             if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMETY)             if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMET)              if(H != nullptr)   H->Write();
   for(auto H : HTrackMETXPeripheral)           if(H != nullptr)   H->Write();
   for(auto H : HTrackMETYPeripheral)           if(H != nullptr)   H->Write();
   for(auto H : HTrackMETPeripheral)            if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMETXPeripheral)   if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMETYPeripheral)   if(H != nullptr)   H->Write();
   for(auto H : HPositiveTrackMETPeripheral)    if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID2PT1)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID2PT2)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID2PT5)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID2PT10)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID4PT1)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID4PT2)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID4PT5)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID4PT10)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID5PT1)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID5PT2)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID5PT5)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID5PT10)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID6PT1)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID6PT2)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID6PT5)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID6PT10)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID7PT1)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID7PT2)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID7PT5)             if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID7PT10)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID22PT1)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID22PT2)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID22PT5)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID22PT10)           if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID23PT1)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID23PT2)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID23PT5)            if(H != nullptr)   H->Write();
   for(auto H : HTrackEtaPhiID23PT10)           if(H != nullptr)   H->Write();
   
   OutputFile.Close();

   return 0;
}



