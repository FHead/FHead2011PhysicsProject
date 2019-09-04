#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CommandLine.h"
#include "ProgressBar.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[]);
double GetCorrection(int hiBin, double eta);
void HistogramXYDivide(TH2D &H);
void HistogramShiftCopy(TH2D &H, TH2D &H2);
void PlotDifference(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, string Name);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input", "Skim.root");
   string OutputFileName = CL.Get("Output", "Plots");
   bool DoEE = CL.GetBool("EE", true);

   TH1D HLeptonCount("HLeptonCount", ";N;", 7, 0, 7);
   TH2D HLeptonCharge("HLeptonCharge", ";LeadingCharge;SubleadingCharge", 2, -2, 2, 2, -2, 2);
   TH2D HLeptonPT("HLeptonPT", ";LeadingPT;SubleadingPT", 100, 0, 100, 100, 0, 100);
   TH2D HLeptonEta("HLeptonEta", ";LeadingEta;SubleadingEta", 100, -3, 3, 100, -3, 3);
   TH2D HLeptonPhi("HLeptonPhi", ";LeadingPhi;SubleadingPhi", 100, -M_PI, M_PI, 100, -M_PI, M_PI);
   TH1D HLepton1PT("HLepton1PT", ";LeadingPT;", 100, 0, 100);
   TH1D HLepton1Eta("HLepton1Eta", ";LeadingEta;", 100, -3, 3);
   TH1D HLepton1Phi("HLepton1Phi", ";LeadingPhi;", 100, -M_PI, M_PI);
   TH1D HLepton2PT("HLepton2PT", ";SubleadingPT;", 100, 0, 100);
   TH1D HLepton2Eta("HLepton2Eta", ";SubleadingEta;", 100, -3, 3);
   TH1D HLepton2Phi("HLepton2Phi", ";SubleadingPhi;", 100, -M_PI, M_PI);
   
   TH1D HDiLeptonPT("HDiLeptonPT", ";LL PT;", 100, 0, 120);
   TH1D HDiLeptonEta("HDiLeptonEta", ";LL Eta;", 100, -5, 5);
   TH1D HDiLeptonY("HDiLeptonY", ";LL Y;", 100, -5, 5);
   TH1D HDiLeptonPhi("HDiLeptonPhi", ";LL Phi;", 100, -M_PI, M_PI);
   TH2D HDiLeptonEtaPhi("HDiLeptonEtaPhi", ";LL Eta;LL Phi", 100, -5, 5, 100, -M_PI, M_PI);
   TH1D HDiLeptonMass("HDiLeptonMass", ";LL Mass;", 100, 55, 125);

   TH1D HTrackCount("HTrackCount", ";N;", 100, 0, 2500);
   TH1D HTrackCountPT1("HTrackCountPT1", ";N;", 100, 0, 1400);
   TH1D HTrackCountPT2("HTrackCountPT2", ";N;", 100, 0, 300);
   TH1D HTrackPT("HTrackPt", ";N;", 100, 0, 100);
   TH1D HTrackEta("HTrackEta", ";N;", 100, -2.5, 2.5);
   TH1D HTrackPhi("HTrackPhi", ";N;", 100, -M_PI, M_PI);
   TH1D HSelectedTrackPT("HSelectedTrackPT", ";N;", 100, 0, 50);
   TH1D HSelectedTrackEta("HSelectedTrackEta", ";N;", 100, -2.5, 2.5);
   TH1D HSelectedTrackPhi("HSelectedTrackPhi", ";N;", 100, -M_PI, M_PI);
   TH1D HSelectedTrackCount("HSelectedTrackCount", ";N;", 100, 0, 2500);
   TH1D HSelectedTrackCountPT1("HSelectedTrackCountPT1", ";N;", 100, 0, 1400);
   TH1D HSelectedTrackCountPT2("HSelectedTrackCountPT2", ";N;", 100, 0, 300);
   
   TH1D HTrackCountMix("HTrackCountMix", ";N;", 100, 0, 2500);
   TH1D HTrackCountPT1Mix("HTrackCountPT1Mix", ";N;", 100, 0, 1400);
   TH1D HTrackCountPT2Mix("HTrackCountPT2Mix", ";N;", 100, 0, 300);
   TH1D HTrackPTMix("HTrackPtMix", ";N;", 100, 0, 100);
   TH1D HTrackEtaMix("HTrackEtaMix", ";N;", 100, -2.5, 2.5);
   TH1D HTrackPhiMix("HTrackPhiMix", ";N;", 100, -M_PI, M_PI);
   TH1D HSelectedTrackPTMix("HSelectedTrackPTMix", ";N;", 100, 0, 50);
   TH1D HSelectedTrackEtaMix("HSelectedTrackEtaMix", ";N;", 100, -2.5, 2.5);
   TH1D HSelectedTrackPhiMix("HSelectedTrackPhiMix", ";N;", 100, -M_PI, M_PI);
   TH1D HSelectedTrackCountMix("HSelectedTrackCountMix", ";N;", 100, 0, 2500);
   TH1D HSelectedTrackCountPT1Mix("HSelectedTrackCountPT1Mix", ";N;", 100, 0, 1400);
   TH1D HSelectedTrackCountPT2Mix("HSelectedTrackCountPT2Mix", ";N;", 100, 0, 300);

   int N = 51;
   TH1D HZTrackDPhi("ZTrackDPhi", ";dphi", N, -M_PI, M_PI);
   TH1D HZTrackDPhiPT1("ZTrackDPhiPT1", ";dphi", N, -M_PI, M_PI);
   TH1D HZTrackDPhiPT2("ZTrackDPhiPT2", ";dphi", N, -M_PI, M_PI);
   TH2D HZTrackPhiPhi("ZTrackPhiPhi", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackPhiPhiPT1("ZTrackPhiPhiPT1", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackPhiPhiPT2("ZTrackPhiPhiPT2", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhi("ZTrackDPhiPhi", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhiPT1("ZTrackDPhiPhiPT1", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhiPT2("ZTrackDPhiPhiPT2", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);
   
   TH1D HZTrackDPhiMix("ZTrackDPhiMix", ";dphi", N, -M_PI, M_PI);
   TH1D HZTrackDPhiPT1Mix("ZTrackDPhiPT1Mix", ";dphi", N, -M_PI, M_PI);
   TH1D HZTrackDPhiPT2Mix("ZTrackDPhiPT2Mix", ";dphi", N, -M_PI, M_PI);
   TH2D HZTrackPhiPhiMix("ZTrackPhiPhiMix", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackPhiPhiPT1Mix("ZTrackPhiPhiPT1Mix", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackPhiPhiPT2Mix("ZTrackPhiPhiPT2Mix", ";Track;Z", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhiMix("ZTrackDPhiPhiMix", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhiPT1Mix("ZTrackDPhiPhiPT1Mix", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);
   TH2D HZTrackDPhiPhiPT2Mix("ZTrackDPhiPhiPT2Mix", ";DPhi;Z phi", N, -M_PI, M_PI, N, -M_PI, M_PI);

   double Tick = M_PI / 20;
   double Bins[] = {0, 3 * Tick, 6 * Tick, 9 * Tick, 12 * Tick, 14 * Tick, 16 * Tick, 18 * Tick, 19 * Tick, 20 * Tick};
   TH1D HDPhiCent0030("HDPhiCent0030", ";#Delta#phi_{trkZ} = |#phi^{trk} - #phi^{Z}|;", 9, Bins);
   TH1D HDPhiCent3090("HDPhiCent3090", ";#Delta#phi_{trkZ} = |#phi^{trk} - #phi^{Z}|;", 9, Bins);
   TH1D HDPhiCent0030Mix("HDPhiCent0030Mix", ";#Delta#phi_{trkZ} = |#phi^{trk} - #phi^{Z}|;", 9, Bins);
   TH1D HDPhiCent3090Mix("HDPhiCent3090Mix", ";#Delta#phi_{trkZ} = |#phi^{trk} - #phi^{Z}|;", 9, Bins);

   TFile File(InputFileName.c_str());

   TTree *HiTree = (TTree *)File.Get("HiTree");
   TTree *MixEventTree = (TTree *)File.Get("mixEventSkim");
   TTree *EventTree = (TTree *)File.Get("EventTree");
   TTree *TrackTree = (TTree *)File.Get("trackSkim");

   int hiBin;
   HiTree->SetBranchAddress("hiBin", &hiBin);

   int nMix;
   MixEventTree->SetBranchAddress("nmix", &nMix);

   int nEle;
   vector<int> *eleCharge = nullptr;
   vector<float> *elePt = nullptr, *eleEta = nullptr, *elePhi = nullptr;
   vector<float> *eleSCEn = nullptr, *eleSCEta = nullptr, *eleSCPhi = nullptr;
   int nMu;
   vector<int> *muCharge = nullptr;
   vector<float> *muPt = nullptr, *muEta = nullptr, *muPhi = nullptr;
   EventTree->SetBranchAddress("nEle", &nEle);
   EventTree->SetBranchAddress("eleCharge", &eleCharge);
   EventTree->SetBranchAddress("elePt", &elePt);
   EventTree->SetBranchAddress("eleEta", &eleEta);
   EventTree->SetBranchAddress("elePhi", &elePhi);
   EventTree->SetBranchAddress("eleSCEn", &eleSCEn);
   EventTree->SetBranchAddress("eleSCEta", &eleSCEta);
   EventTree->SetBranchAddress("eleSCPhi", &eleSCPhi);
   EventTree->SetBranchAddress("nMu", &nMu);
   EventTree->SetBranchAddress("muCharge", &muCharge);
   EventTree->SetBranchAddress("muPt", &muPt);
   EventTree->SetBranchAddress("muEta", &muEta);
   EventTree->SetBranchAddress("muPhi", &muPhi);

   int nTrk;
   vector<float> *trkPt = nullptr, *trkEta = nullptr, *trkPhi = nullptr, *trkWeight = nullptr;
   vector<int> *pfType = nullptr;
   int nTrk_mix;
   vector<float> *trkPt_mix = nullptr, *trkEta_mix = nullptr, *trkPhi_mix = nullptr, *trkWeight_mix = nullptr;
   vector<int> *pfType_mix = nullptr;
   TrackTree->SetBranchAddress("nTrk", &nTrk);
   TrackTree->SetBranchAddress("trkPt", &trkPt);
   TrackTree->SetBranchAddress("trkEta", &trkEta);
   TrackTree->SetBranchAddress("trkPhi", &trkPhi);
   TrackTree->SetBranchAddress("trkWeight", &trkWeight);
   TrackTree->SetBranchAddress("pfType", &pfType);
   TrackTree->SetBranchAddress("nTrk_mix", &nTrk_mix);
   TrackTree->SetBranchAddress("trkPt_mix", &trkPt_mix);
   TrackTree->SetBranchAddress("trkEta_mix", &trkEta_mix);
   TrackTree->SetBranchAddress("trkPhi_mix", &trkPhi_mix);
   TrackTree->SetBranchAddress("trkWeight_mix", &trkWeight_mix);
   TrackTree->SetBranchAddress("pfType_mix", &pfType_mix);

   double ZCount = 0;
   double ZCount0030 = 0, ZCount3090 = 0;

   int EntryCount = EventTree->GetEntries();
   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      HiTree->GetEntry(iE);
      MixEventTree->GetEntry(iE);
      EventTree->GetEntry(iE);
      TrackTree->GetEntry(iE);

      int nLepton = (DoEE ? nEle : nMu);

      HLeptonCount.Fill(nLepton);

      FourVector P1, P2;
      
      map<double, FourVector> Leptons;
      for(int i = 0; i < nLepton; i++)
      {
         double Correction = (DoEE ? GetCorrection(hiBin, (*eleSCEta)[i]) : 1);

         if(DoEE)
            if((*eleSCEta)[i] < -1.392 && (*eleSCPhi)[i] < -0.872665 && (*eleSCPhi)[i] > -1.570796)
               continue;

         FourVector P;
         if(DoEE)
            P.SetPtEtaPhiMass((*elePt)[i] * Correction, (*eleEta)[i], (*elePhi)[i], 0.000511);
         else
            P.SetPtEtaPhiMass((*muPt)[i] * Correction, (*muEta)[i], (*muPhi)[i], 0.105658);

         if(DoEE == true && (*eleCharge)[i] < 0)
            P[0] = -P[0];
         if(DoEE == false && (*muCharge)[i] < 0)
            P[0] = -P[0];

         Leptons.insert(pair<double, FourVector>(-P.GetPT(), P));
      }

      if(Leptons.size() < 2)
         continue;

      map<double, FourVector>::iterator iter = Leptons.begin();
      P1 = iter->second;
      iter++;
      P2 = iter->second;
      if(GetDR(P1, P2) < 0.2 && iter != Leptons.end())
      {
         iter++;
         if(iter != Leptons.end())
            P2 = iter->second;
         else
            P2.SetPtEtaPhiMass(0, 0, 0, 0);
      }

      int Charge1 = (P1[0] > 0) ? 1 : -1;
      int Charge2 = (P2[0] > 0) ? 1 : -1;

      P1[0] = fabs(P1[0]);
      P2[0] = fabs(P2[0]);

      if(P1.GetPT() < 20)
         continue;
      if(P2.GetPT() < 20)
         continue;

      if(P1.GetAbsEta() > 2.1)
         continue;
      if(P2.GetAbsEta() > 2.1)
         continue;

      HLeptonCharge.Fill(Charge1, Charge2);
      HLeptonPT.Fill(P1.GetPT(), P2.GetPT());
      HLeptonEta.Fill(P1.GetEta(), P2.GetEta());
      HLeptonPhi.Fill(P1.GetPhi(), P2.GetPhi());
      HLepton1PT.Fill(P1.GetPT());
      HLepton1Eta.Fill(P1.GetEta());
      HLepton1Phi.Fill(P1.GetPhi());
      HLepton2PT.Fill(P2.GetPT());
      HLepton2Eta.Fill(P2.GetEta());
      HLepton2Phi.Fill(P2.GetPhi());

      FourVector LL = P1 + P2;

      HDiLeptonPT.Fill(LL.GetPT());
      HDiLeptonEta.Fill(LL.GetEta());
      HDiLeptonY.Fill(LL.GetY());
      HDiLeptonPhi.Fill(LL.GetPhi());
      HDiLeptonEtaPhi.Fill(LL.GetEta(), LL.GetPhi());
      HDiLeptonMass.Fill(LL.GetMass());

      if(Charge1 == Charge2)
         continue;
      if(LL.GetPT() < 30)
         continue;
      if(LL.GetMass() < 60 || LL.GetMass() > 120)
         continue;

      double ZY = LL.GetY();
      double ZWeight = 1;
      if(DoEE == true)
         ZWeight = 1 / max(0.05, 0.95 - 0.0550816 * ZY * ZY - 0.0449184 * ZY * ZY * ZY * ZY);

      ZCount = ZCount + ZWeight;
      if(hiBin >= 0 && hiBin < 60)
         ZCount0030 = ZCount0030 + ZWeight;
      if(hiBin > 60 && hiBin < 180)
         ZCount3090 = ZCount3090 + ZWeight;

      double TrackCount = 0, TrackCountPT1 = 0, TrackCountPT2 = 0;
      double SelectedTrackCount = 0, SelectedTrackCountPT1 = 0, SelectedTrackCountPT2 = 0;
      for(int i = 0; i < nTrk; i++)
      {
         if((*pfType)[i] != 1)
            continue;

         FourVector P;
         P.SetPtEtaPhi((*trkPt)[i], (*trkEta)[i], (*trkPhi)[i]);
         double W = (*trkWeight)[i] * ZWeight;

         if(P.GetPT() > 0)   TrackCount += W;
         if(P.GetPT() > 1)   TrackCountPT1 += W;
         if(P.GetPT() > 2)   TrackCountPT2 += W;

         HTrackPT.Fill(P.GetPT(), W);
         HTrackEta.Fill(P.GetEta(), W);
         HTrackPhi.Fill(P.GetPhi(), W);

         // if(GetDR(P, P1) < 0.8)    continue;
         // if(GetDR(P, P2) < 0.8)    continue;

         HSelectedTrackPT.Fill(P.GetPT(), W);
         HSelectedTrackEta.Fill(P.GetEta(), W);
         HSelectedTrackPhi.Fill(P.GetPhi(), W);
         
         if(P.GetPT() > 0)   SelectedTrackCount += W;
         if(P.GetPT() > 1)   SelectedTrackCountPT1 += W;
         if(P.GetPT() > 2)   SelectedTrackCountPT2 += W;

         double DPhi = P.GetPhi() - LL.GetPhi();
         if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
         if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

         if(P.GetPT() > 0)   HZTrackDPhi.Fill(DPhi, W);
         if(P.GetPT() > 1)   HZTrackDPhiPT1.Fill(DPhi, W);
         if(P.GetPT() > 2)   HZTrackDPhiPT2.Fill(DPhi, W);
         if(P.GetPT() > 0)   HZTrackPhiPhi.Fill(P.GetPhi(), LL.GetPhi(), W);
         if(P.GetPT() > 1)   HZTrackPhiPhiPT1.Fill(P.GetPhi(), LL.GetPhi(), W);
         if(P.GetPT() > 2)   HZTrackPhiPhiPT2.Fill(P.GetPhi(), LL.GetPhi(), W);

         if(P.GetPT() > 1)
         {
            if(hiBin >= 0 && hiBin < 60)
               HDPhiCent0030.Fill(fabs(DPhi), W);
            if(hiBin >= 60 && hiBin < 180)
               HDPhiCent3090.Fill(fabs(DPhi), W);
         }
      }

      HTrackCount.Fill(TrackCount);
      HTrackCountPT1.Fill(TrackCountPT1);
      HTrackCountPT2.Fill(TrackCountPT2);
      HSelectedTrackCount.Fill(SelectedTrackCount);
      HSelectedTrackCountPT1.Fill(SelectedTrackCountPT1);
      HSelectedTrackCountPT2.Fill(SelectedTrackCountPT2);

      double TrackCountMix = 0, TrackCountPT1Mix = 0, TrackCountPT2Mix = 0;
      double SelectedTrackCountMix = 0, SelectedTrackCountPT1Mix = 0, SelectedTrackCountPT2Mix = 0;
      for(int i = 0; i < nTrk_mix; i++)
      {
         if((*pfType_mix)[i] != 1)
            continue;

         FourVector P;
         P.SetPtEtaPhi((*trkPt_mix)[i], (*trkEta_mix)[i], (*trkPhi_mix)[i]);
         double W = (*trkWeight_mix)[i] / nMix * ZWeight;

         if(P.GetPT() > 0)   TrackCountMix += W;
         if(P.GetPT() > 1)   TrackCountPT1Mix += W;
         if(P.GetPT() > 2)   TrackCountPT2Mix += W;

         HTrackPTMix.Fill(P.GetPT(), W);
         HTrackEtaMix.Fill(P.GetEta(), W);
         HTrackPhiMix.Fill(P.GetPhi(), W);

         // if(GetDR(P, P1) < 0.8)    continue;
         // if(GetDR(P, P2) < 0.8)    continue;

         HSelectedTrackPTMix.Fill(P.GetPT(), W);
         HSelectedTrackEtaMix.Fill(P.GetEta(), W);
         HSelectedTrackPhiMix.Fill(P.GetPhi(), W);
         
         if(P.GetPT() > 0)   SelectedTrackCountMix += W;
         if(P.GetPT() > 1)   SelectedTrackCountPT1Mix += W;
         if(P.GetPT() > 2)   SelectedTrackCountPT2Mix += W;

         double DPhi = P.GetPhi() - LL.GetPhi();
         if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
         if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

         if(P.GetPT() > 0)   HZTrackDPhiMix.Fill(DPhi, W);
         if(P.GetPT() > 1)   HZTrackDPhiPT1Mix.Fill(DPhi, W);
         if(P.GetPT() > 2)   HZTrackDPhiPT2Mix.Fill(DPhi, W);
         if(P.GetPT() > 0)   HZTrackPhiPhiMix.Fill(P.GetPhi(), LL.GetPhi(), W);
         if(P.GetPT() > 1)   HZTrackPhiPhiPT1Mix.Fill(P.GetPhi(), LL.GetPhi(), W);
         if(P.GetPT() > 2)   HZTrackPhiPhiPT2Mix.Fill(P.GetPhi(), LL.GetPhi(), W);

         if(P.GetPT() > 1)
         {
            if(hiBin >= 0 && hiBin < 60)
               HDPhiCent0030Mix.Fill(fabs(DPhi), W);
            if(hiBin >= 60 && hiBin < 180)
               HDPhiCent3090Mix.Fill(fabs(DPhi), W);
         }
      }

      HTrackCountMix.Fill(TrackCountMix);
      HTrackCountPT1Mix.Fill(TrackCountPT1Mix);
      HTrackCountPT2Mix.Fill(TrackCountPT2Mix);
      HSelectedTrackCountMix.Fill(SelectedTrackCountMix);
      HSelectedTrackCountPT1Mix.Fill(SelectedTrackCountPT1Mix);
      HSelectedTrackCountPT2Mix.Fill(SelectedTrackCountPT2Mix);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HDPhiCent0030.Scale(1.0 / ZCount0030);
   HDPhiCent3090.Scale(1.0 / ZCount3090);
   HDPhiCent0030Mix.Scale(1.0 / ZCount0030);
   HDPhiCent3090Mix.Scale(1.0 / ZCount3090);
   for(int i = 1; i <= HDPhiCent0030.GetNbinsX(); i++)
   {
      double BinSize = HDPhiCent0030.GetXaxis()->GetBinUpEdge(i) - HDPhiCent0030.GetXaxis()->GetBinLowEdge(i);
      HDPhiCent0030.SetBinContent(i, HDPhiCent0030.GetBinContent(i) / BinSize);
      HDPhiCent0030.SetBinError(i, HDPhiCent0030.GetBinError(i) / BinSize);
      HDPhiCent3090.SetBinContent(i, HDPhiCent3090.GetBinContent(i) / BinSize);
      HDPhiCent3090.SetBinError(i, HDPhiCent3090.GetBinError(i) / BinSize);
      HDPhiCent0030Mix.SetBinContent(i, HDPhiCent0030Mix.GetBinContent(i) / BinSize);
      HDPhiCent0030Mix.SetBinError(i, HDPhiCent0030Mix.GetBinError(i) / BinSize);
      HDPhiCent3090Mix.SetBinContent(i, HDPhiCent3090Mix.GetBinContent(i) / BinSize);
      HDPhiCent3090Mix.SetBinError(i, HDPhiCent3090Mix.GetBinError(i) / BinSize);
   }

   File.Close();

   TFile OutputFile((OutputFileName + ".root").c_str(), "RECREATE");

   PdfFileHelper PdfFile(OutputFileName + ".pdf");
   PdfFile.AddTextPage("Z-Hadron plots");

   PdfFile.AddTextPage("Lepton plots");

   PdfFile.AddPlot(HLeptonCount, "hist text00", true);
   PdfFile.AddPlot(HLeptonCharge, "colz text00");
   PdfFile.AddPlot(HLeptonPT, "colz");
   PdfFile.AddPlot(HLeptonEta, "colz");
   PdfFile.AddPlot(HLeptonPhi, "colz");
   PdfFile.AddPlot(HLepton1PT, "");
   PdfFile.AddPlot(HLepton1Eta, "");
   PdfFile.AddPlot(HLepton1Phi, "");
   PdfFile.AddPlot(HLepton2PT, "");
   PdfFile.AddPlot(HLepton2Eta, "");
   PdfFile.AddPlot(HLepton2Phi, "");
   PdfFile.AddPlot(HDiLeptonPT, "");
   PdfFile.AddPlot(HDiLeptonEta, "");
   PdfFile.AddPlot(HDiLeptonY, "");
   PdfFile.AddPlot(HDiLeptonPhi, "");
   PdfFile.AddPlot(HDiLeptonEtaPhi, "colz");
   PdfFile.AddPlot(HDiLeptonMass, "");

   PdfFile.AddTextPage("Track plots");

   PdfFile.AddPlot(HTrackCount, "hist", true);
   PdfFile.AddPlot(HTrackCountPT1, "hist", true);
   PdfFile.AddPlot(HTrackCountPT2, "hist", true);
   PdfFile.AddPlot(HTrackPT, "", true);
   PdfFile.AddPlot(HTrackEta, "");
   PdfFile.AddPlot(HTrackPhi, "");
   PdfFile.AddPlot(HSelectedTrackPT, "", true);
   PdfFile.AddPlot(HSelectedTrackEta, "");
   PdfFile.AddPlot(HSelectedTrackPhi, "");
   PdfFile.AddPlot(HSelectedTrackCount, "hist", true);
   PdfFile.AddPlot(HSelectedTrackCountPT1, "hist", true);
   PdfFile.AddPlot(HSelectedTrackCountPT2, "hist", true);
   
   PdfFile.AddPlot(HZTrackDPhi, "");
   PdfFile.AddPlot(HZTrackDPhiPT1, "");
   PdfFile.AddPlot(HZTrackDPhiPT2, "");
   PdfFile.AddPlot(HZTrackPhiPhi, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT1, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT2, "colz");

   HDPhiCent0030.SetStats(0);
   HDPhiCent3090.SetStats(0);
   PdfFile.AddPlot(HDPhiCent0030, "");
   PdfFile.AddPlot(HDPhiCent3090, "");

   HistogramXYDivide(HZTrackPhiPhi);
   HistogramXYDivide(HZTrackPhiPhiPT1);
   HistogramXYDivide(HZTrackPhiPhiPT2);

   PdfFile.AddPlot(HZTrackPhiPhi, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT1, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT2, "colz");

   HistogramShiftCopy(HZTrackPhiPhi, HZTrackDPhiPhi);
   HistogramShiftCopy(HZTrackPhiPhiPT1, HZTrackDPhiPhiPT1);
   HistogramShiftCopy(HZTrackPhiPhiPT2, HZTrackDPhiPhiPT2);

   PdfFile.AddPlot(HZTrackDPhiPhi, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT1, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT2, "colz");

   HistogramXYDivide(HZTrackDPhiPhi);
   HistogramXYDivide(HZTrackDPhiPhiPT1);
   HistogramXYDivide(HZTrackDPhiPhiPT2);

   PdfFile.AddPlot(HZTrackDPhiPhi, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT1, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT2, "colz");

   PdfFile.AddTextPage("Mix plots");

   PdfFile.AddPlot(HTrackCountMix, "hist", true);
   PdfFile.AddPlot(HTrackCountPT1Mix, "hist", true);
   PdfFile.AddPlot(HTrackCountPT2Mix, "hist", true);
   PdfFile.AddPlot(HTrackPTMix, "", true);
   PdfFile.AddPlot(HTrackEtaMix, "");
   PdfFile.AddPlot(HTrackPhiMix, "");
   PdfFile.AddPlot(HSelectedTrackPTMix, "", true);
   PdfFile.AddPlot(HSelectedTrackEtaMix, "");
   PdfFile.AddPlot(HSelectedTrackPhiMix, "");
   PdfFile.AddPlot(HSelectedTrackCountMix, "hist", true);
   PdfFile.AddPlot(HSelectedTrackCountPT1Mix, "hist", true);
   PdfFile.AddPlot(HSelectedTrackCountPT2Mix, "hist", true);

   PdfFile.AddPlot(HZTrackDPhiMix, "");
   PdfFile.AddPlot(HZTrackDPhiPT1Mix, "");
   PdfFile.AddPlot(HZTrackDPhiPT2Mix, "");
   PdfFile.AddPlot(HZTrackPhiPhiMix, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT1Mix, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT2Mix, "colz");

   HDPhiCent0030Mix.SetStats(0);
   HDPhiCent3090Mix.SetStats(0);
   PdfFile.AddPlot(HDPhiCent0030Mix, "");
   PdfFile.AddPlot(HDPhiCent3090Mix, "");

   HistogramXYDivide(HZTrackPhiPhiMix);
   HistogramXYDivide(HZTrackPhiPhiPT1Mix);
   HistogramXYDivide(HZTrackPhiPhiPT2Mix);

   PdfFile.AddPlot(HZTrackPhiPhiMix, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT1Mix, "colz");
   PdfFile.AddPlot(HZTrackPhiPhiPT2Mix, "colz");

   HistogramShiftCopy(HZTrackPhiPhiMix, HZTrackDPhiPhiMix);
   HistogramShiftCopy(HZTrackPhiPhiPT1Mix, HZTrackDPhiPhiPT1Mix);
   HistogramShiftCopy(HZTrackPhiPhiPT2Mix, HZTrackDPhiPhiPT2Mix);

   PdfFile.AddPlot(HZTrackDPhiPhiMix, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT1Mix, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT2Mix, "colz");

   HistogramXYDivide(HZTrackDPhiPhiMix);
   HistogramXYDivide(HZTrackDPhiPhiPT1Mix);
   HistogramXYDivide(HZTrackDPhiPhiPT2Mix);

   PdfFile.AddPlot(HZTrackDPhiPhiMix, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT1Mix, "colz");
   PdfFile.AddPlot(HZTrackDPhiPhiPT2Mix, "colz");

   PdfFile.AddTextPage("Subtracted plots");

   PlotDifference(PdfFile, HDPhiCent0030, HDPhiCent0030Mix, "HDPhiCent0030Subtracted");
   PlotDifference(PdfFile, HDPhiCent3090, HDPhiCent3090Mix, "HDPhiCent3090Subtracted");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.Close();

   return 0;
}

double GetCorrection(int hiBin, double eta)
{
   eta = fabs(eta);

   if(eta < 1.442)
   {
      if(hiBin < 20)   return 0.990;
      if(hiBin < 60)   return 1.006;
      return 1.016;
   }
   if(eta > 1.566 && eta < 2.5)
   {
      if(hiBin < 20)   return 0.976;
      if(hiBin < 60)   return 1.015;
      return 1.052;
   }

   return 0;
}

void HistogramXYDivide(TH2D &H)
{
   TH1D *H1 = (TH1D *)H.ProjectionX();
   TH1D *H2 = (TH1D *)H.ProjectionY();

   for(int iX = 1; iX <= H1->GetNbinsX(); iX++)
      for(int iY = 1; iY <= H2->GetNbinsX(); iY++)
         H.SetBinContent(iX, iY, H.GetBinContent(iX, iY) / H1->GetBinContent(iX) / H2->GetBinContent(iY));
}

void HistogramShiftCopy(TH2D &H1, TH2D &H2)
{
   int NX = H1.GetNbinsX();
   int NY = H1.GetNbinsY();

   for(int iX = 1; iX <= NX; iX++)
      for(int iY = 1; iY <= NY; iY++)
         H2.SetBinContent(iX, iY, H1.GetBinContent((iX + NX / 2 + iY - 2) % NX + 1, iY));
}

void PlotDifference(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, string Name)
{
   TH1D *H = (TH1D *)H1.Clone(Name.c_str());
   H->Add(&H2, -1);
   H->SetMinimum(0);
   H->SetMaximum(25);

   H->Write();

   PdfFile.AddPlot(H);
}




