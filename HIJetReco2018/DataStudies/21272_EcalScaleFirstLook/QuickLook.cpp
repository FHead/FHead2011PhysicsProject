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
#include "TProfile.h"

#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "Messenger.h"

int main(int argc, char *argv[]);
double CalculateEndcapFraction(double Eta, double JetR, double Halfway);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputFileName         = CL.Get("Output", "Result.root");
   string JetTreeName            = CL.Get("Tree", "ak4PFJetAnalyzer/t");
   bool RemoveHEM                = CL.GetBool("RemoveHEM", false);
   bool IsCalo                   = CL.GetBool("IsCalo", true);
   bool Algo6Rejection           = CL.GetBool("Algo6Rejection", false);
   double CBarrel                = CL.GetDouble("CBarrel", 0.99277375);
   double CEndcap                = CL.GetDouble("CEndcap", 1.1537139);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   double BarrelEndcapEta        = CL.GetDouble("BarrelEndcapEta", 1.479);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", "", 1, 0, 1);

   TH1D HPTHat("HPTHat", ";#hat{p}_{T};", 100, 0, 300);

   TH1D HRefPT("HRefPT", "|#eta| < 2.5;Gen p_{T};", 100, 0, 300);
   TH1D HRefPT_EtaN25N15("HRefPT_EtaN25N15", "-2.5 < #eta < -1.5;Gen p_{T};", 100, 0, 300);
   TH1D HRefPT_EtaN15N00("HRefPT_EtaN15N00", "-1.5 < #eta < 0;Gen p_{T};", 100, 0, 300);
   TH1D HRefPT_EtaP00P15("HRefPT_EtaP00P15", "0 < #eta < 1.5;Gen p_{T};", 100, 0, 300);
   TH1D HRefPT_EtaP15P25("HRefPT_EtaP15P25", "1.5 < #eta < 2.5;Gen p_{T};", 100, 0, 300);
   TH2D HRefEtaPhi("HRefEtaPhi", ";Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HRefEtaPhi_PT30("HRefEtaPhi_PT30", "Gen p_{T} > 30;Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HRefEtaPhi_PT50("HRefEtaPhi_PT50", "Gen p_{T} > 50;Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HRefEtaPhi_PT75("HRefEtaPhi_PT75", "Gen p_{T} > 75;Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HRefEtaPhi_PT100("HRefEtaPhi_PT100", "Gen p_{T} > 100;Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HRefEtaPhi_PT125("HRefEtaPhi_PT125", "Gen p_{T} > 125;Gen #eta;Gen #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   TH1D HJetPT("HJetPT", "|#eta| < 2.5;Jet p_{T};", 100, 0, 300);
   TH1D HJetPT_EtaN25N15("HJetPT_EtaN25N15", "-2.5 < #eta < -1.5;Jet p_{T};", 100, 0, 300);
   TH1D HJetPT_EtaN15N00("HJetPT_EtaN15N00", "-1.5 < #eta < 0;Jet p_{T};", 100, 0, 300);
   TH1D HJetPT_EtaP00P15("HJetPT_EtaP00P15", "0 < #eta < 1.5;Jet p_{T};", 100, 0, 300);
   TH1D HJetPT_EtaP15P25("HJetPT_EtaP15P25", "1.5 < #eta < 2.5;Jet p_{T};", 100, 0, 300);
   TH2D HJetEtaPhi("HJetEtaPhi", ";Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_PT30("HJetEtaPhi_PT30", "Jet p_{T} > 30;Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_PT50("HJetEtaPhi_PT50", "Jet p_{T} > 50;Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_PT75("HJetEtaPhi_PT75", "Jet p_{T} > 75;Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_PT100("HJetEtaPhi_PT100", "Jet p_{T} > 100;Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);
   TH2D HJetEtaPhi_PT125("HJetEtaPhi_PT125", "Jet p_{T} > 125;Jet #eta;Jet #phi", 100, -2.5, 2.5, 100, -M_PI, M_PI);

   TH2D HRVsEta_PT30_PT50("HRVsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HRVsEta_PT50_PT75("HRVsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HRVsEta_PT75_PT100("HRVsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HRVsEta_PT50_PT100("HRVsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HRVsEta_PT100_PT125("HRVsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HRVsPT_EtaN25N15("HRVsPT_EtaN25N15", "-2.5 < #eta < -1.5;p_{T};Response", 100, 0, 300, 100, 0, 2.5);
   TH2D HRVsPT_EtaN15N00("HRVsPT_EtaN15N00", "-1.5 < #eta < 0.0;p_{T};Response", 100, 0, 300, 100, 0, 2.5);
   TH2D HRVsPT_EtaP00P15("HRVsPT_EtaP00P15", "0.0 < #eta < 1.5;p_{T};Response", 100, 0, 300, 100, 0, 2.5);
   TH2D HRVsPT_EtaP15P25("HRVsPT_EtaP15P25", "1.5 < #eta < 2.5;p_{T};Response", 100, 0, 300, 100, 0, 2.5);
   
   TProfile PRVsEta_PT30_PT50("PRVsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Response", 100, -2.5, 2.5);
   TProfile PRVsEta_PT50_PT75("PRVsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Response", 100, -2.5, 2.5);
   TProfile PRVsEta_PT75_PT100("PRVsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Response", 100, -2.5, 2.5);
   TProfile PRVsEta_PT50_PT100("PRVsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Response", 100, -2.5, 2.5);
   TProfile PRVsEta_PT100_PT125("PRVsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Response", 100, -2.5, 2.5);
   TProfile PRVsPT_EtaN25N15("PRVsPT_EtaN25N15", "-2.5 < #eta < -1.5;p_{T};Response", 100, 0, 200);
   TProfile PRVsPT_EtaN15N00("PRVsPT_EtaN15N00", "-1.5 < #eta < 0.0;p_{T};Response", 100, 0, 200);
   TProfile PRVsPT_EtaP00P15("PRVsPT_EtaP00P15", "0.0 < #eta < 1.5;p_{T};Response", 100, 0, 200);
   TProfile PRVsPT_EtaP15P25("PRVsPT_EtaP15P25", "1.5 < #eta < 2.5;p_{T};Response", 100, 0, 200);

   TH2D HRVsAbsEta_PT30_PT50("HRVsAbsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HRVsAbsEta_PT50_PT75("HRVsAbsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HRVsAbsEta_PT75_PT100("HRVsAbsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HRVsAbsEta_PT50_PT100("HRVsAbsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HRVsAbsEta_PT100_PT125("HRVsAbsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Response", 40, 0.0, 2.5, 300, 0, 2.5);
   
   TProfile PRVsAbsEta_PT30_PT50("PRVsAbsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Response", 40, 0.0, 2.5);
   TProfile PRVsAbsEta_PT50_PT75("PRVsAbsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Response", 40, 0.0, 2.5);
   TProfile PRVsAbsEta_PT75_PT100("PRVsAbsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Response", 40, 0.0, 2.5);
   TProfile PRVsAbsEta_PT50_PT100("PRVsAbsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Response", 40, 0.0, 2.5);
   TProfile PRVsAbsEta_PT100_PT125("PRVsAbsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Response", 40, 0.0, 2.5);

   TH2D HEtaVsFractionInEndcap("HEtaVsFractionInEndcap", ";#eta;f_{endcap}", 75, -2.5, 2.5, 75, -0.1, 1.1);
   TH2D HEtaVsFractionInEndcapZoomed("HEtaVsFractionInEndcapZoomed", ";#eta;f_{endcap}", 75, 1, 2, 75, -0.1, 1.1);

   TH2D HJetPTVsJetCPT("HJetPTVsJetCPT", ";Jet p_{T};Corrected jet p_{T}", 100, 0, 200, 100, 0, 200);
   
   TH2D HCRVsEta_PT30_PT50("HCRVsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Corrected response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HCRVsEta_PT50_PT75("HCRVsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Corrected response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HCRVsEta_PT75_PT100("HCRVsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Corrected response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HCRVsEta_PT50_PT100("HCRVsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Corrected response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HCRVsEta_PT100_PT125("HCRVsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Corrected response", 100, -2.5, 2.5, 300, 0, 2.5);
   TH2D HCRVsPT_EtaN25N15("HCRVsPT_EtaN25N15", "-2.5 < #eta < -1.5;p_{T};Corrected response", 100, 0, 300, 100, 0, 2.5);
   TH2D HCRVsPT_EtaN15N00("HCRVsPT_EtaN15N00", "-1.5 < #eta < 0.0;p_{T};Corrected response", 100, 0, 300, 100, 0, 2.5);
   TH2D HCRVsPT_EtaP00P15("HCRVsPT_EtaP00P15", "0.0 < #eta < 1.5;p_{T};Corrected response", 100, 0, 300, 100, 0, 2.5);
   TH2D HCRVsPT_EtaP15P25("HCRVsPT_EtaP15P25", "1.5 < #eta < 2.5;p_{T};Corrected response", 100, 0, 300, 100, 0, 2.5);
   
   TProfile PCRVsEta_PT30_PT50("PCRVsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Corrected response", 100, -2.5, 2.5);
   TProfile PCRVsEta_PT50_PT75("PCRVsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Corrected response", 100, -2.5, 2.5);
   TProfile PCRVsEta_PT75_PT100("PCRVsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Corrected response", 100, -2.5, 2.5);
   TProfile PCRVsEta_PT50_PT100("PCRVsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Corrected response", 100, -2.5, 2.5);
   TProfile PCRVsEta_PT100_PT125("PCRVsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Corrected response", 100, -2.5, 2.5);
   TProfile PCRVsPT_EtaN25N15("PCRVsPT_EtaN25N15", "-2.5 < #eta < -1.5;p_{T};Corrected response", 100, 0, 200);
   TProfile PCRVsPT_EtaN15N00("PCRVsPT_EtaN15N00", "-1.5 < #eta < 0.0;p_{T};Corrected response", 100, 0, 200);
   TProfile PCRVsPT_EtaP00P15("PCRVsPT_EtaP00P15", "0.0 < #eta < 1.5;p_{T};Corrected response", 100, 0, 200);
   TProfile PCRVsPT_EtaP15P25("PCRVsPT_EtaP15P25", "1.5 < #eta < 2.5;p_{T};Corrected response", 100, 0, 200);

   TH2D HCRVsAbsEta_PT30_PT50("HCRVsAbsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Corrected response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HCRVsAbsEta_PT50_PT75("HCRVsAbsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Corrected response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HCRVsAbsEta_PT75_PT100("HCRVsAbsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Corrected response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HCRVsAbsEta_PT50_PT100("HCRVsAbsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Corrected response", 40, 0.0, 2.5, 300, 0, 2.5);
   TH2D HCRVsAbsEta_PT100_PT125("HCRVsAbsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Corrected response", 40, 0.0, 2.5, 300, 0, 2.5);
   
   TProfile PCRVsAbsEta_PT30_PT50("PCRVsAbsEta_PT30_PT50", "30 < p_{T}^{Gen} < 50;#eta;Corrected response", 40, 0.0, 2.5);
   TProfile PCRVsAbsEta_PT50_PT75("PCRVsAbsEta_PT50_PT75", "50 < p_{T}^{Gen} < 75;#eta;Corrected response", 40, 0.0, 2.5);
   TProfile PCRVsAbsEta_PT75_PT100("PCRVsAbsEta_PT75_PT100", "75 < p_{T}^{Gen} < 100;#eta;Corrected response", 40, 0.0, 2.5);
   TProfile PCRVsAbsEta_PT50_PT100("PCRVsAbsEta_PT50_PT100", "50 < p_{T}^{Gen} < 100;#eta;Corrected response", 40, 0.0, 2.5);
   TProfile PCRVsAbsEta_PT100_PT125("PCRVsAbsEta_PT100_PT125", "100 < p_{T}^{Gen} < 125;#eta;Corrected response", 40, 0.0, 2.5);

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MHiEvent(InputFile);
      JetTreeMessenger MJet(InputFile, JetTreeName);
      TriggerTreeMessenger MHLT(InputFile);
      PFTreeMessenger MPF(InputFile);
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
         if(iE < 500 || (iE % (EntryCount / 300)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }


         MHiEvent.GetEntry(iE);
         MJet.GetEntry(iE);
         MHLT.GetEntry(iE);
         MPF.GetEntry(iE);
         MTrack.GetEntry(iE);

         HPTHat.Fill(MJet.PTHat);

         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            if(MJet.JetEta[iJ] < -2.5 || MJet.JetEta[iJ] > 2.5)
               continue;

            if(RemoveHEM == true)
               if(MJet.JetEta[iJ] > -3.5 && MJet.JetEta[iJ] < -1.0
                  && MJet.JetPhi[iJ] > -2.1 && MJet.JetPhi[iJ] < -0.5)
                  continue;

            double JetCPT = MJet.JetPT[iJ];

            if(IsCalo == true)
            {
               double FractionInEndcap = CalculateEndcapFraction(MJet.JetEta[iJ], JetR, BarrelEndcapEta);
               double JetEMF = ((MJet.EcalSum[iJ] + MJet.HcalSum[iJ] > 0) ? MJet.EcalSum[iJ] / (MJet.EcalSum[iJ] + MJet.HcalSum[iJ]) : 0);
               double Had = MJet.JetPT[iJ] * (1 - JetEMF);
               double EM_Barrel = MJet.JetPT[iJ] * JetEMF * (1 - FractionInEndcap);
               double EM_Endcap = MJet.JetPT[iJ] * JetEMF * FractionInEndcap;

               JetCPT = Had + EM_Barrel * CBarrel + EM_Endcap * CEndcap;

               HEtaVsFractionInEndcap.Fill(MJet.JetEta[iJ], FractionInEndcap);
               HEtaVsFractionInEndcapZoomed.Fill(MJet.JetEta[iJ], FractionInEndcap);
            }
            else   // it's PF!
            {
               double AllPT = 0;
               double AllCPT = 0;

               int NPF = MPF.ID->size();
               for(int iPF = 0; iPF < NPF; iPF++)
               {
                  if((*MPF.Eta)[iPF] < MJet.JetEta[iJ] - JetR)   continue;
                  if((*MPF.Eta)[iPF] > MJet.JetEta[iJ] + JetR)   continue;

                  double DEta = (*MPF.Eta)[iPF] - MJet.JetEta[iJ];
                  double DPhi = (*MPF.Phi)[iPF] - MJet.JetPhi[iJ];
                  if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
                  if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

                  if(DEta * DEta + DPhi * DPhi > JetR * JetR)
                     continue;

                  AllPT = AllPT + (*MPF.PT)[iPF];

                  if((*MPF.ID)[iPF] == 4)   // PF Photon!
                  {
                     if((*MPF.Eta)[iPF] > -BarrelEndcapEta && (*MPF.Eta)[iPF] < BarrelEndcapEta)
                        AllCPT = AllCPT + (*MPF.PT)[iPF] * CBarrel;
                     else
                        AllCPT = AllCPT + (*MPF.PT)[iPF] * CEndcap;
                  }
                  else
                     AllCPT = AllCPT + (*MPF.PT)[iPF];
               }

               JetCPT = MJet.JetPT[iJ] * AllCPT / AllPT;
            }

            if(IsCalo == false && Algo6Rejection == true)
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

                  if(DEta * DEta + DPhi * DPhi > 0.4 * 0.4)
                     continue;

                  AllPT = AllPT + MTrack.TrackPT[iT];
                  if(MTrack.TrackAlgo[iT] == 6)
                     Algo6PT = Algo6PT + MTrack.TrackPT[iT];
               }

               if(AllPT > 0 && Algo6PT / AllPT > 0.25)
                  continue;
            }

            HJetPTVsJetCPT.Fill(MJet.JetPT[iJ], JetCPT);

            HRefPT.Fill(MJet.RefPT[iJ]);
            if(MJet.RefEta[iJ] > -2.5 && MJet.RefEta[iJ] < -1.5)   HRefPT_EtaN25N15.Fill(MJet.RefPT[iJ]);
            if(MJet.RefEta[iJ] > -1.5 && MJet.RefEta[iJ] < 0.0)    HRefPT_EtaN15N00.Fill(MJet.RefPT[iJ]);
            if(MJet.RefEta[iJ] > 0.0 && MJet.RefEta[iJ] < 1.5)     HRefPT_EtaP00P15.Fill(MJet.RefPT[iJ]);
            if(MJet.RefEta[iJ] > 1.5 && MJet.RefEta[iJ] < 2.5)     HRefPT_EtaP15P25.Fill(MJet.RefPT[iJ]);
            
            HRefEtaPhi.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);
            if(MJet.RefPT[iJ] > 30)    HRefEtaPhi_PT30.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);
            if(MJet.RefPT[iJ] > 50)    HRefEtaPhi_PT50.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);
            if(MJet.RefPT[iJ] > 75)    HRefEtaPhi_PT75.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);
            if(MJet.RefPT[iJ] > 100)   HRefEtaPhi_PT100.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);
            if(MJet.RefPT[iJ] > 125)   HRefEtaPhi_PT125.Fill(MJet.RefEta[iJ], MJet.RefPhi[iJ]);

            HJetPT.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > -2.5 && MJet.JetEta[iJ] < -1.5)   HJetPT_EtaN25N15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 0.0)    HJetPT_EtaN15N00.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > 0.0 && MJet.JetEta[iJ] < 1.5)     HJetPT_EtaP00P15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < 2.5)     HJetPT_EtaP15P25.Fill(MJet.JetPT[iJ]);
            
            HJetEtaPhi.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 30)    HJetEtaPhi_PT30.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 50)    HJetEtaPhi_PT50.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 75)    HJetEtaPhi_PT75.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 100)   HJetEtaPhi_PT100.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 125)   HJetEtaPhi_PT125.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
   
            if(MJet.RefPT[iJ] > 30 && MJet.RefPT[iJ] < 50)
            {
               HRVsEta_PT30_PT50.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsEta_PT30_PT50.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HRVsAbsEta_PT30_PT50.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsAbsEta_PT30_PT50.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsEta_PT30_PT50.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsEta_PT30_PT50.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               HCRVsAbsEta_PT30_PT50.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
               PCRVsAbsEta_PT30_PT50.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefPT[iJ] > 50 && MJet.RefPT[iJ] < 75)
            {
               HRVsEta_PT50_PT75.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsEta_PT50_PT75.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HRVsAbsEta_PT50_PT75.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsAbsEta_PT50_PT75.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsEta_PT50_PT75.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsEta_PT50_PT75.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               HCRVsAbsEta_PT50_PT75.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
               PCRVsAbsEta_PT50_PT75.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefPT[iJ] > 75 && MJet.RefPT[iJ] < 100)
            {
               HRVsEta_PT75_PT100.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsEta_PT75_PT100.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HRVsAbsEta_PT75_PT100.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsAbsEta_PT75_PT100.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsEta_PT75_PT100.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsEta_PT75_PT100.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               HCRVsAbsEta_PT75_PT100.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
               PCRVsAbsEta_PT75_PT100.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefPT[iJ] > 50 && MJet.RefPT[iJ] < 100)
            {
               HRVsEta_PT50_PT100.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsEta_PT50_PT100.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HRVsAbsEta_PT50_PT100.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsAbsEta_PT50_PT100.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsEta_PT50_PT100.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsEta_PT50_PT100.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               HCRVsAbsEta_PT50_PT100.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
               PCRVsAbsEta_PT50_PT100.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefPT[iJ] > 100 && MJet.RefPT[iJ] < 125)
            {
               HRVsEta_PT100_PT125.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsEta_PT100_PT125.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HRVsAbsEta_PT100_PT125.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsAbsEta_PT100_PT125.Fill(fabs(MJet.RefEta[iJ]), MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsEta_PT100_PT125.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsEta_PT100_PT125.Fill(MJet.RefEta[iJ], JetCPT / MJet.RefPT[iJ]);
               HCRVsAbsEta_PT100_PT125.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
               PCRVsAbsEta_PT100_PT125.Fill(fabs(MJet.RefEta[iJ]), JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefEta[iJ] > -2.5 && MJet.RefEta[iJ] < -1.5)
            {
               HRVsPT_EtaN25N15.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsPT_EtaN25N15.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsPT_EtaN25N15.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsPT_EtaN25N15.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefEta[iJ] > -1.5 && MJet.RefEta[iJ] < 0.0)
            {
               HRVsPT_EtaN15N00.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsPT_EtaN15N00.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsPT_EtaN15N00.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsPT_EtaN15N00.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefEta[iJ] > 0.0 && MJet.RefEta[iJ] < 1.5)
            {
               HRVsPT_EtaP00P15.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsPT_EtaP00P15.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsPT_EtaP00P15.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsPT_EtaP00P15.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
            }
            if(MJet.RefEta[iJ] > 1.5 && MJet.RefEta[iJ] < 2.5)
            {
               HRVsPT_EtaP15P25.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               PRVsPT_EtaP15P25.Fill(MJet.RefPT[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ]);
               HCRVsPT_EtaP15P25.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
               PCRVsPT_EtaP15P25.Fill(MJet.RefPT[iJ], JetCPT / MJet.RefPT[iJ]);
            }
         }

         HN.Fill(0);
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();

   HN.Write();

   HPTHat.Write();

   HRefPT.Write();
   HRefPT_EtaN25N15.Write();
   HRefPT_EtaN15N00.Write();
   HRefPT_EtaP00P15.Write();
   HRefPT_EtaP15P25.Write();
   HRefEtaPhi.Write();
   HRefEtaPhi_PT30.Write();
   HRefEtaPhi_PT50.Write();
   HRefEtaPhi_PT75.Write();
   HRefEtaPhi_PT100.Write();
   HRefEtaPhi_PT125.Write();

   HJetPT.Write();
   HJetPT_EtaN25N15.Write();
   HJetPT_EtaN15N00.Write();
   HJetPT_EtaP00P15.Write();
   HJetPT_EtaP15P25.Write();
   HJetEtaPhi.Write();
   HJetEtaPhi_PT30.Write();
   HJetEtaPhi_PT50.Write();
   HJetEtaPhi_PT75.Write();
   HJetEtaPhi_PT100.Write();
   HJetEtaPhi_PT125.Write();

   HRVsEta_PT30_PT50.Write();
   HRVsEta_PT50_PT75.Write();
   HRVsEta_PT75_PT100.Write();
   HRVsEta_PT50_PT100.Write();
   HRVsEta_PT100_PT125.Write();
   HRVsPT_EtaN25N15.Write();
   HRVsPT_EtaN15N00.Write();
   HRVsPT_EtaP00P15.Write();
   HRVsPT_EtaP15P25.Write();
   
   PRVsEta_PT30_PT50.Write();
   PRVsEta_PT50_PT75.Write();
   PRVsEta_PT75_PT100.Write();
   PRVsEta_PT50_PT100.Write();
   PRVsEta_PT100_PT125.Write();
   PRVsPT_EtaN25N15.Write();
   PRVsPT_EtaN15N00.Write();
   PRVsPT_EtaP00P15.Write();
   PRVsPT_EtaP15P25.Write();

   HRVsAbsEta_PT30_PT50.Write();
   HRVsAbsEta_PT50_PT75.Write();
   HRVsAbsEta_PT75_PT100.Write();
   HRVsAbsEta_PT50_PT100.Write();
   HRVsAbsEta_PT100_PT125.Write();
   
   PRVsAbsEta_PT30_PT50.Write();
   PRVsAbsEta_PT50_PT75.Write();
   PRVsAbsEta_PT75_PT100.Write();
   PRVsAbsEta_PT50_PT100.Write();
   PRVsAbsEta_PT100_PT125.Write();

   HCRVsEta_PT30_PT50.Write();
   HCRVsEta_PT50_PT75.Write();
   HCRVsEta_PT75_PT100.Write();
   HCRVsEta_PT50_PT100.Write();
   HCRVsEta_PT100_PT125.Write();
   HCRVsPT_EtaN25N15.Write();
   HCRVsPT_EtaN15N00.Write();
   HCRVsPT_EtaP00P15.Write();
   HCRVsPT_EtaP15P25.Write();
   
   PCRVsEta_PT30_PT50.Write();
   PCRVsEta_PT50_PT75.Write();
   PCRVsEta_PT75_PT100.Write();
   PCRVsEta_PT50_PT100.Write();
   PCRVsEta_PT100_PT125.Write();
   PCRVsPT_EtaN25N15.Write();
   PCRVsPT_EtaN15N00.Write();
   PCRVsPT_EtaP00P15.Write();
   PCRVsPT_EtaP15P25.Write();

   HCRVsAbsEta_PT30_PT50.Write();
   HCRVsAbsEta_PT50_PT75.Write();
   HCRVsAbsEta_PT75_PT100.Write();
   HCRVsAbsEta_PT50_PT100.Write();
   HCRVsAbsEta_PT100_PT125.Write();
   
   PCRVsAbsEta_PT30_PT50.Write();
   PCRVsAbsEta_PT50_PT75.Write();
   PCRVsAbsEta_PT75_PT100.Write();
   PCRVsAbsEta_PT50_PT100.Write();
   PCRVsAbsEta_PT100_PT125.Write();

   HEtaVsFractionInEndcap.Write();
   HEtaVsFractionInEndcapZoomed.Write();

   HJetPTVsJetCPT.Write();

   OutputFile.Close();

   return 0;
}

double CalculateEndcapFraction(double Eta, double JetR, double Halfway)
{
   Eta = fabs(Eta);
   double FractionInEndcap = 0;

   if(Eta < Halfway - JetR)
      FractionInEndcap = 0.0;
   else if(Eta > Halfway + JetR)
      FractionInEndcap = 1.0;
   else
   {
      bool Flip = false;

      if(Eta > Halfway)
      {
         Flip = true;
         Eta = Halfway - (Eta - Halfway);
      }

      double Theta = acos((Halfway - Eta) / JetR);
      double FanArea = Theta;   // times R^2
      double TriangleArea = cos(Theta) * sin(Theta);   // times R^2
      double Area = FanArea - TriangleArea;   // times R^2

      FractionInEndcap = Area / M_PI;   // R^2 cancels

      if(Flip == true)
         FractionInEndcap = 1 - FractionInEndcap;
   }

   return FractionInEndcap;
}


