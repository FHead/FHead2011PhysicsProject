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

#include "PlotHelper.h"
#include "DrawRandom.h"
#include "TauHelperFunctions.h"
#include "ReadNTPTree.h"

int main(int argc, char *argv[]);
void RecoLevelReference(string InputLQMass = "250");

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

   // Calo jet histograms
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

   // PF jet histograms
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

   // Loop through events
   int NumberOfEvents = NTPTree->GetEntries();
   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << endl;

      NTPTree->GetEntry(iEvent);

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

      HNAK5Jet.Fill(M.nAK5Jet);
      for(int i = 0; i < M.nAK5Jet; i++)
      {
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
      }
      if(SubLeadingAK5JetIndex >= 0)
      {
         HSubLeadingAK5JetPT.Fill(GetPT(SubLeadingAK5JetP));
         HSubLeadingAK5JetPhi.Fill(GetPhi(SubLeadingAK5JetP));
         HSubLeadingAK5JetEta.Fill(GetEta(SubLeadingAK5JetP));
      }
      if(LeadingAK5JetIndex >= 0 && SubLeadingAK5JetIndex >= 0)
      {
         HLeadingTwoAK5JetsPTVsPT.Fill(GetPT(LeadingAK5JetP), GetPT(SubLeadingAK5JetP));
         HLeadingTwoAK5JetsDPhi.Fill(GetDPhi(LeadingAK5JetP, SubLeadingAK5JetP));
         HLeadingTwoAK5JetsDR.Fill(GetDR(LeadingAK5JetP, SubLeadingAK5JetP));
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

      HNPFJet.Fill(M.nAK5PFJet);
      for(int i = 0; i < M.nAK5PFJet; i++)
      {
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
      }
      if(SubLeadingPFJetIndex >= 0)
      {
         HSubLeadingPFJetPT.Fill(GetPT(SubLeadingPFJetP));
         HSubLeadingPFJetPhi.Fill(GetPhi(SubLeadingPFJetP));
         HSubLeadingPFJetEta.Fill(GetEta(SubLeadingPFJetP));
      }
      if(LeadingPFJetIndex >= 0 && SubLeadingPFJetIndex >= 0)
      {
         HLeadingTwoPFJetsPTVsPT.Fill(GetPT(LeadingPFJetP), GetPT(SubLeadingPFJetP));
         HLeadingTwoPFJetsDPhi.Fill(GetDPhi(LeadingPFJetP, SubLeadingPFJetP));
         HLeadingTwoPFJetsDR.Fill(GetDR(LeadingPFJetP, SubLeadingPFJetP));
      }
   }

   // Add histograms to output
   PsFile.AddTextPage("Calo jet plots");
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
   
   PsFile.AddTextPage("PF jet plots");
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
  
   // Close things 
   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

