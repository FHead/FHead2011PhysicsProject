#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TROOT.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"

#include "DrawRandom.h"
#include "PlotHelper.h"
#include "GenparticleTree.h"
#include "TauHelperFunctions.h"

int main(int argc, char *argv[]);
void PileUpStudy(string InputMass, double MeanPileUp);
GenParticleTree GenerateAndFillTree(Pythia &pythia);
template<class T> void AddTwoPanelPlot(PsFileHelper &PsFile, T &Plot1, T &Plot2, string Option,
   bool LogY = false, bool LogZ = false);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   TStyle gStyle;
   
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
   Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
   Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
   Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);

   string InputMass = "250";
   if(argc > 1)
      InputMass = argv[1];

   PileUpStudy(InputMass, 10);
}

void PileUpStudy(string InputMass, double MeanPileUp)
{
   Pythia pythia;
   pythia.readString("SoftQCD:minBias = on");   // turn on min bias event generation
   pythia.readString("Random:setSeed = on");    // use random seed
   pythia.readString("Random:seed = 0");        // seed == time, ie., no repetition if rerun
   pythia.readString("Tune:pp = 5");            // pp collision tune 4C
   pythia.init(2212, 2212, 7000);

   ifstream in(("Samples/LQ" + InputMass + "Sample").c_str());

   TH1D HPileUpNumber("HPileUpNumber", "Number of pile-ups", 31, -0.5, 30.5);

   TH1D HLQStableParticleCount("HLQStableParticleCount", "Stable particle count in LQ sample", 100, 0, 3000);
   TH1D HStableParticleCount("HStableParticleCount", "Stable particle count with pile-up", 100, 0, 3000);
   TH1D HLQTotalVisibleEnergy("HLQTotalVisibleEnergy",
      "Total energy of visible particles within eta 2.4 in LQ sample", 100, 0, 3000);
   TH1D HTotalVisibleEnergy("HTotalVisibleEnergy",
      "Total energy of visible particles within eta 2.4, with pileup", 100, 0, 3000);
   TH1D HMET("HMET", "Transverse missing energy", 100, 0, 1000);
   TH1D HLQMET("HLQMET", "Transverse missing energy, LQ sample", 100, 0, 1000);

   TH1D HLQNJet15("HLQNJet15", "Number of jets with pt > 15 in LQ sample", 30, -0.5, 29.5);
   TH1D HLQNJet30("HLQNJet30", "Number of jets with pt > 30 in LQ sample", 30, -0.5, 29.5);
   TH1D HLQNJet50("HLQNJet50", "Number of jets with pt > 50 in LQ sample", 30, -0.5, 29.5);
   TH1D HLQNJet100("HLQNJet100", "Number of jets with pt > 100 in LQ sample", 30, -0.5, 29.5);
   TH1D HLQNJet150("HLQNJet150", "Number of jets with pt > 150 in LQ sample", 30, -0.5, 29.5);
   TH1D HNJet15("HNJet15", "Number of jets with pt > 15", 30, -0.5, 29.5);
   TH1D HNJet30("HNJet30", "Number of jets with pt > 30", 30, -0.5, 29.5);
   TH1D HNJet50("HNJet50", "Number of jets with pt > 50", 30, -0.5, 29.5);
   TH1D HNJet100("HNJet100", "Number of jets with pt > 100", 30, -0.5, 29.5);
   TH1D HNJet150("HNJet150", "Number of jets with pt > 150", 30, -0.5, 29.5);

   TH1D HLeadingJetPT("HLeadingJetPT", "Leading jet pt", 100, 0, 500);
   TH1D HSubLeadingJetPT("HSubLeadingJetPT", "Sub-leading jet pt", 100, 0, 500);
   TH2D HLeadingTwoJetsPTVsPT("HLeadingTwoJetsPTVsPT", "Leading PT vs. Sub-leading jet pt",
      100, 0, 500, 100, 0, 500);
   TH1D HLQLeadingJetPT("HLQLeadingJetPT", "Leading jet pt, LQ sample", 100, 0, 500);
   TH1D HLQSubLeadingJetPT("HLQSubLeadingJetPT", "Sub-leading jet pt, LQ sample", 100, 0, 500);
   TH2D HLQLeadingTwoJetsPTVsPT("HLQLeadingTwoJetsPTVsPT", "Leading PT vs. Sub-leading jet pt, LQ sample",
      100, 0, 500, 100, 0, 500);

   TH1D HLeadingJetPTChange("HLeadingJetPTChange", "PT change of leading jet;After - Before", 100, -100, 100);
   TH1D HSubLeadingJetPTChange("HSubLeadingJetPTChange", "PT change of sub-leading jet;After - Before",
      100, -100, 100);
   TH2D HLeadingJetDeltaEtaPhi("HLeadingJetDeltaEtaPhi", "Leading jet delta eta/phi before and after PU;eta;phi",
      100, -1, 1, 100, -1, 1);
   TH2D HSubLeadingJetDeltaEtaPhi("HSubLeadingJetDeltaEtaPhi",
      "Sub-leading jet delta eta/phi before and after PU;eta;phi", 100, -1, 1, 100, -1, 1);

   TH1D HMRFromJets("HMRFromJets", "MR distribution from jets", 100, 0, 1000);
   TH1D HMRTFromJets("HMRTFromJets", "MRT distribution from jets", 100, 0, 500);
   TH1D HRFromJets("HRFromJets", "R distribution from jets", 100, 0, 1);
   TH2D HMRVsRFromJets("HMRVsRFromJets", "MR vs. R distribution from jets;MR;R", 100, 0, 1000, 100, 0, 1);

   TH1D HLQMRFromJets("HLQMRFromJets", "LQ MR distribution from jets", 100, 0, 1000);
   TH1D HLQMRTFromJets("HLQMRTFromJets", "LQ MRT distribution from jets", 100, 0, 500);
   TH1D HLQRFromJets("HLQRFromJets", "LQ R distribution from jets", 100, 0, 1);
   TH2D HLQMRVsRFromJets("HLQMRVsRFromJets", "LQ MR vs. R distribution from jets;MR;R", 100, 0, 1000, 100, 0, 1);

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);
   int EventCount = Helper.IntValue;

   for(int iEvent = 0; iEvent < EventCount; iEvent++)
   {
      if((iEvent + 1) % 100 == 0)
         cout << "Processing event " << iEvent + 1 << "/" << EventCount << endl;
      if(iEvent >= 25000)
         break;

      GenParticleTree Tree;
      Tree.LoadFromStream(in);
      HLQStableParticleCount.Fill(ListStableParticle(Tree).size());

      int OriginalParticleCount = Tree.ParticleCount();

      double LQTotalEnergy = 0;
      double LQTotalP[4] = {0, 0, 0, 0};
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)
            continue;
         if(Tree[i].StatusCode != 1)
            continue;
         if(fabs(GetEta(Tree[i].P)) > 2.4)
            continue;

         LQTotalEnergy = LQTotalEnergy + Tree[i].P[0];

         LQTotalP[0] = LQTotalP[0] + Tree[i].P[0];
         LQTotalP[1] = LQTotalP[1] + Tree[i].P[1];
         LQTotalP[2] = LQTotalP[2] + Tree[i].P[2];
         LQTotalP[3] = LQTotalP[3] + Tree[i].P[3];
      }
      HLQTotalVisibleEnergy.Fill(LQTotalEnergy);

      double LQME[4] = {GetPT(LQTotalP), -LQTotalP[1], -LQTotalP[2], 0};
      HLQMET.Fill(GetPT(LQME));
      
      // add some pile-ups
      int PileUpNumber = (int)DrawPoisson(MeanPileUp);
      for(int i = 0; i < PileUpNumber; i++)
         Tree = Tree + GenerateAndFillTree(pythia);
      
      HPileUpNumber.Fill(PileUpNumber);
      HStableParticleCount.Fill(ListStableParticle(Tree).size());
      
      double TotalEnergy = 0;
      double TotalP[4] = {0, 0, 0, 0};
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)
            continue;
         if(Tree[i].StatusCode != 1)
            continue;
         if(fabs(GetEta(Tree[i].P)) > 2.4)
            continue;

         TotalEnergy = TotalEnergy + Tree[i].P[0];

         TotalP[0] = TotalP[0] + Tree[i].P[0];
         TotalP[1] = TotalP[1] + Tree[i].P[1];
         TotalP[2] = TotalP[2] + Tree[i].P[2];
         TotalP[3] = TotalP[3] + Tree[i].P[3];
      }
      HTotalVisibleEnergy.Fill(TotalEnergy);

      double ME[4] = {GetPT(TotalP), -TotalP[1], -TotalP[2], 0};
      HMET.Fill(GetPT(ME));

      // Now cluster jets
      vector<PseudoJet> LQInputParticles;
      vector<PseudoJet> InputParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)
            continue;
         if(Tree[i].StatusCode != 1)
            continue;
         if(fabs(GetEta(Tree[i].P)) > 2.4)
            continue;

         InputParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         if(i < OriginalParticleCount)
            LQInputParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
      }

      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(InputParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(1);
      
      JetDefinition LQDefinition(antikt_algorithm, 0.5);
      ClusterSequence LQSequence(LQInputParticles, LQDefinition);
      vector<PseudoJet> LQJets = LQSequence.inclusive_jets(1);

      multimap<double, int, greater<double> > SortJets;
      multimap<double, int, greater<double> > LQSortJets;

      int NJet15 = 0;
      int NJet30 = 0;
      int NJet50 = 0;
      int NJet100 = 0;
      int NJet150 = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         double PT = Jets[i].perp();
         if(PT > 15)    NJet15 = NJet15 + 1;
         if(PT > 30)    NJet30 = NJet30 + 1;
         if(PT > 50)    NJet50 = NJet50 + 1;
         if(PT > 100)   NJet100 = NJet100 + 1;
         if(PT > 150)   NJet150 = NJet150 + 1;

         SortJets.insert(pair<double, int>(PT, i));
      }
      HNJet15.Fill(NJet15);
      HNJet30.Fill(NJet30);
      HNJet50.Fill(NJet50);
      HNJet100.Fill(NJet100);
      HNJet150.Fill(NJet150);
      
      int LQNJet15 = 0;
      int LQNJet30 = 0;
      int LQNJet50 = 0;
      int LQNJet100 = 0;
      int LQNJet150 = 0;
      for(int i = 0; i < (int)LQJets.size(); i++)
      {
         double PT = LQJets[i].perp();
         if(PT > 15)    LQNJet15 = LQNJet15 + 1;
         if(PT > 30)    LQNJet30 = LQNJet30 + 1;
         if(PT > 50)    LQNJet50 = LQNJet50 + 1;
         if(PT > 100)   LQNJet100 = LQNJet100 + 1;
         if(PT > 150)   LQNJet150 = LQNJet150 + 1;
         
         LQSortJets.insert(pair<double, int>(PT, i));
      }
      HLQNJet15.Fill(LQNJet15);
      HLQNJet30.Fill(LQNJet30);
      HLQNJet50.Fill(LQNJet50);
      HLQNJet100.Fill(LQNJet100);
      HLQNJet150.Fill(LQNJet150);

      int LeadingJetIndex = -1;
      int SubLeadingJetIndex = -1;
      if(SortJets.size() > 0)
         LeadingJetIndex = SortJets.begin()->second;
      if(SortJets.size() > 1)
      {
         multimap<double, int>::iterator iter = SortJets.begin();
         iter++;
         SubLeadingJetIndex = iter->second;
      }
      
      int LQLeadingJetIndex = -1;
      int LQSubLeadingJetIndex = -1;
      if(LQSortJets.size() > 0)
         LQLeadingJetIndex = LQSortJets.begin()->second;
      if(LQSortJets.size() > 1)
      {
         multimap<double, int>::iterator iter = LQSortJets.begin();
         iter++;
         LQSubLeadingJetIndex = iter->second;
      }

      if(LeadingJetIndex >= 1)     HLeadingJetPT.Fill(Jets[LeadingJetIndex].perp());
      if(LeadingJetIndex >= 2)     HSubLeadingJetPT.Fill(Jets[SubLeadingJetIndex].perp());
      if(LQLeadingJetIndex >= 1)   HLQLeadingJetPT.Fill(LQJets[LQLeadingJetIndex].perp());
      if(LQLeadingJetIndex >= 2)   HLQSubLeadingJetPT.Fill(LQJets[LQSubLeadingJetIndex].perp());
      
      if(LeadingJetIndex >= 2)
         HLeadingTwoJetsPTVsPT.Fill(Jets[LeadingJetIndex].perp(), Jets[SubLeadingJetIndex].perp());
      if(LQLeadingJetIndex >= 2)
         HLQLeadingTwoJetsPTVsPT.Fill(LQJets[LQLeadingJetIndex].perp(), LQJets[LQSubLeadingJetIndex].perp());

      double LeadingJetP[4] = {0, 0, 0, 0};
      double SubLeadingJetP[4] = {0, 0, 0, 0};
      double LQLeadingJetP[4] = {0, 0, 0, 0};
      double LQSubLeadingJetP[4] = {0, 0, 0, 0};

      if(LeadingJetIndex >= 0)
      {
         LeadingJetP[0] = Jets[LeadingJetIndex].e();
         LeadingJetP[1] = Jets[LeadingJetIndex].px();
         LeadingJetP[2] = Jets[LeadingJetIndex].py();
         LeadingJetP[3] = Jets[LeadingJetIndex].pz();
      }
      if(SubLeadingJetIndex >= 0)
      {
         SubLeadingJetP[0] = Jets[SubLeadingJetIndex].e();
         SubLeadingJetP[1] = Jets[SubLeadingJetIndex].px();
         SubLeadingJetP[2] = Jets[SubLeadingJetIndex].py();
         SubLeadingJetP[3] = Jets[SubLeadingJetIndex].pz();
      }
      if(LQLeadingJetIndex >= 0)
      {
         LQLeadingJetP[0] = LQJets[LQLeadingJetIndex].e();
         LQLeadingJetP[1] = LQJets[LQLeadingJetIndex].px();
         LQLeadingJetP[2] = LQJets[LQLeadingJetIndex].py();
         LQLeadingJetP[3] = LQJets[LQLeadingJetIndex].pz();
      }
      if(LQSubLeadingJetIndex >= 0)
      {
         LQSubLeadingJetP[0] = LQJets[LQSubLeadingJetIndex].e();
         LQSubLeadingJetP[1] = LQJets[LQSubLeadingJetIndex].px();
         LQSubLeadingJetP[2] = LQJets[LQSubLeadingJetIndex].py();
         LQSubLeadingJetP[3] = LQJets[LQSubLeadingJetIndex].pz();
      }

      if(LeadingJetIndex >= 0 && LQLeadingJetIndex >= 0)
      {
         HLeadingJetPTChange.Fill(GetPT(LeadingJetP) - GetPT(LQLeadingJetP));
         HLeadingJetDeltaEtaPhi.Fill(GetEta(LeadingJetP) - GetEta(LQLeadingJetP),
            GetDPhi(LeadingJetP, LQLeadingJetP));
      }
      if(SubLeadingJetIndex >= 0 && LQSubLeadingJetIndex >= 0)
      {
         HSubLeadingJetPTChange.Fill(GetPT(SubLeadingJetP) - GetPT(LQSubLeadingJetP));
         HSubLeadingJetDeltaEtaPhi.Fill(GetEta(SubLeadingJetP) - GetEta(LQSubLeadingJetP),
            GetDPhi(SubLeadingJetP, LQSubLeadingJetP));
      }

      if(LeadingJetIndex >= 0 && SubLeadingJetIndex >= 0)
      {
         double MRFromJets = GetMR(LeadingJetP, SubLeadingJetP);
         double MRTFromJets = GetMRT(LeadingJetP, SubLeadingJetP, ME);
         double RFromJets = GetR(LeadingJetP, SubLeadingJetP, ME);
         HMRFromJets.Fill(MRFromJets);
         HMRTFromJets.Fill(MRTFromJets);
         HRFromJets.Fill(RFromJets);
         HMRVsRFromJets.Fill(MRFromJets, RFromJets);
      }
      if(LQLeadingJetIndex >= 0 && LQSubLeadingJetIndex >= 0)
      {
         double LQMRFromJets = GetMR(LQLeadingJetP, LQSubLeadingJetP);
         double LQMRTFromJets = GetMRT(LQLeadingJetP, LQSubLeadingJetP, LQME);
         double LQRFromJets = GetR(LQLeadingJetP, LQSubLeadingJetP, LQME);
         HLQMRFromJets.Fill(LQMRFromJets);
         HLQMRTFromJets.Fill(LQMRTFromJets);
         HLQRFromJets.Fill(LQRFromJets);
         HLQMRVsRFromJets.Fill(LQMRFromJets, LQRFromJets);
      }
   }

   PsFileHelper PsFile(("PileUpStudy_" + InputMass + "GeV.ps").c_str());
   PsFile.AddTextPage("Gen-level pileup study!");

   vector<string> Explanation;
   Explanation.push_back("LQ Sample: PTHIA6 D6T, generated with CMSSW 3_11_0");
   Explanation.push_back("Input mass: " + InputMass + " GeV");
   Explanation.push_back("");
   Explanation.push_back("Minbias generated with PYTHIA8 4C tune, turning on \"SoftQCD:minBias\" flag");
   Explanation.push_back("Number of additional interaction is drawn from Poisson, mean 10");
   Explanation.push_back("Generated particles are added together directly, no vertex positioning");
   Explanation.push_back("");
   Explanation.push_back("For anything two-panel, left: before, right: after pileup added");
   PsFile.AddTextPage(Explanation);

   PsFile.AddTextPage("Basic comparison before and after pileup");
   PsFile.AddPlot(HPileUpNumber, "", false);
   AddTwoPanelPlot(PsFile, HLQStableParticleCount, HStableParticleCount, "", true);
   AddTwoPanelPlot(PsFile, HLQTotalVisibleEnergy, HTotalVisibleEnergy, "", true);
   AddTwoPanelPlot(PsFile, HLQMET, HMET, "", true);

   PsFile.AddTextPage("Jets after pileup");
   AddTwoPanelPlot(PsFile, HLQNJet15, HNJet15, "", true);
   AddTwoPanelPlot(PsFile, HLQNJet30, HNJet30, "", true);
   AddTwoPanelPlot(PsFile, HLQNJet50, HNJet50, "", true);
   AddTwoPanelPlot(PsFile, HLQNJet100, HNJet100, "", true);
   AddTwoPanelPlot(PsFile, HLQNJet150, HNJet150, "", true);
   AddTwoPanelPlot(PsFile, HLQLeadingJetPT, HLeadingJetPT, "", true);
   AddTwoPanelPlot(PsFile, HLQSubLeadingJetPT, HSubLeadingJetPT, "", true);
   AddTwoPanelPlot(PsFile, HLQLeadingTwoJetsPTVsPT, HLeadingTwoJetsPTVsPT, "colz", false);
   PsFile.AddPlot(HLeadingJetPTChange, "", true);
   PsFile.AddPlot(HSubLeadingJetPTChange, "", true);
   PsFile.AddPlot(HLeadingJetDeltaEtaPhi, "colz", false);
   PsFile.AddPlot(HSubLeadingJetDeltaEtaPhi, "colz", false);

   PsFile.AddTextPage("MR, R from leading jets");
   AddTwoPanelPlot(PsFile, HLQMRFromJets, HMRFromJets, "", true);
   AddTwoPanelPlot(PsFile, HLQMRTFromJets, HMRTFromJets, "", true);
   AddTwoPanelPlot(PsFile, HLQRFromJets, HRFromJets, "", true);
   AddTwoPanelPlot(PsFile, HLQMRVsRFromJets, HMRVsRFromJets, "colz", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   in.close();
}

GenParticleTree GenerateAndFillTree(Pythia &pythia)
{
   pythia.next();

   vector<GenParticle> particles(pythia.event.size());
   
   for(int j = 0; j < pythia.event.size(); j++)
   {
      particles[j].P[0] = pythia.event[j].e();
      particles[j].P[1] = pythia.event[j].px();
      particles[j].P[2] = pythia.event[j].py();
      particles[j].P[3] = pythia.event[j].pz();

      particles[j].V[0] = pythia.event[j].tProd();
      particles[j].V[1] = pythia.event[j].xProd();
      particles[j].V[2] = pythia.event[j].yProd();
      particles[j].V[3] = pythia.event[j].zProd();

      particles[j].PDGID = pythia.event[j].id();
      particles[j].StatusCode = pythia.event.statusHepMC(j);

      particles[j].Mothers = pythia.event.motherList(j);
      particles[j].Daughters = pythia.event.daughterList(j);
   }

   return GenParticleTree(particles, 0, 0, true);   // give a random runnumber and eventnumber
}

template<class T> void AddTwoPanelPlot(PsFileHelper &PsFile, T &Plot1, T &Plot2, string Option,
   bool LogY, bool LogZ)
{
   TCanvas canvas("C", "C", 0, 0, 1024, 512);

   canvas.Divide(2);

   canvas.cd(1);
   Plot1.Draw(Option.c_str());

   canvas.cd(2);
   Plot2.Draw(Option.c_str());

   if(LogY == true)
   {
      canvas.cd(1)->SetLogy();
      canvas.cd(2)->SetLogy();
   }
   if(LogZ == true)
   {
      canvas.cd(1)->SetLogz();
      canvas.cd(2)->SetLogz();
   }

   PsFile.AddCanvas(canvas);
}



