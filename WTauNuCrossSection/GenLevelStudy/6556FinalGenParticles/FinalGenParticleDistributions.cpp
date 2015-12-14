#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "TH1D.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "PlotHelper.h"

#include "GenparticleTree.h"
#include "TauHelperFunctions.h"

int main();
void FinalGenParticleDistributions();
void FinalGenParticleDistributions(string Input, string OutputBase, int Category = 0);
map<int, int> ReadChargedParticles();
vector<PseudoJet> ExtractTracks(GenParticleTree Tree, double PTMin, map<int, int> AllowedPDGList);

int main()
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

   FinalGenParticleDistributions();
}

void FinalGenParticleDistributions()
{
   // run these first
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category6", 6);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category7", 7);
   FinalGenParticleDistributions("Samples/6555TopSample", "Top");
   FinalGenParticleDistributions("Samples/6555QCDPTHatMin20Sample", "QCD");

   // then the rest
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category1", 1);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category2", 2);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category3", 3);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category4", 4);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category5", 5);
   FinalGenParticleDistributions("Samples/6554TauEnrichedWSample", "Signal_Category8", 8);
   FinalGenParticleDistributions("Samples/6555WENuSample", "WENu");
   FinalGenParticleDistributions("Samples/6555WMuNuSample", "WMuNu");
   FinalGenParticleDistributions("Samples/6555ZTauTauSample", "ZTauTau");
}

void FinalGenParticleDistributions(string Input, string OutputBase, int Category)
{
   cout << "Start looping for sample " << OutputBase << endl;

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   ifstream in(Input.c_str());

   int Size = 0;
   in >> Size;

   // declare histograms
   TH1D HMETWhole("HMETWhole", "Missing energy distribution of final (non-neutrino) particles, no eta cut",
      100, 0, 100);
   TH1D HMET("HMET", "Missing energy distribution of final (non-neutrino) particles (|eta| < 2.4)", 100, 0, 100);
   TH1D HNJet15("HNJet15", "Jet count with 15 GeV threshold", 10, -0.5, 9.5);
   TH1D HNJet20("HNJet20", "Jet count with 20 GeV threshold", 10, -0.5, 9.5);
   TH1D HNJet30("HNJet30", "Jet count with 30 GeV threshold", 10, -0.5, 9.5);
   TH1D HTauJetDR("HTauJetDR", "DR between gen-level tau and closest jet", 100, 0, 1);
   TH1D HTauJetPTRatio("HTauJetPTRatio", "PT ratio: closest jet / gen-level tau", 100, 0, 3);
   TH1D HTauJetMultiplicity("HTauJetMultiplicity", "Number of constituents in jet closest to true tau",
      20, -0.5, 19.5);
   TH1D HJetMultiplicity15("HJetMultiplicity15", "Jet multiplicty, 15 GeV", 20, -0.5, 19.5);
   TH1D HJetMultiplicity20("HJetMultiplicity25", "Jet multiplicty, 25 GeV", 20, -0.5, 19.5);
   TH1D HJetMultiplicity30("HJetMultiplicity30", "Jet multiplicty, 30 GeV", 20, -0.5, 19.5);
   TH1D HMinRadius3ProngJet("HMinRadius3ProngJet", "Min radius of a jet with 3 constituents", 100, 0, 0.3);
   TH1D HMinRadius3ProngJet15("HMinRadius3ProngJet15", "Min radius of a jet with 3 constituents, 15", 100, 0, 0.3);
   TH1D HMinRadius3ProngJet20("HMinRadius3ProngJet20", "Min radius of a jet with 3 constituents, 20", 100, 0, 0.3);
   TH1D HMinRadius3ProngJet30("HMinRadius3ProngJet30", "Min radius of a jet with 3 constituents, 30", 100, 0, 0.3);

   // list of charged particles
   map<int, int> ChargedPDGID = ReadChargedParticles();

   for(int iEvent = 0; iEvent < Size; iEvent++)
   {
      // for the impatient people
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing event " << iEvent + 1 << "/" << Size << endl;
      // if(iEvent > 25000)   // debug mode
      //    break;

      // read event
      GenParticleTree Tree;
      Tree.LoadFromStream(in);

      bool ExistTauInEvent = HasTau(Tree);
      int TauIndex = -1;

      // check category if it is signal event
      if(Category != 0 && ExistTauInEvent == true)
      {
         int category = -1;
         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            if(Tree[i].PDGID != -15 && Tree[i].PDGID != 15)   // want a tau to begin with
               continue;

            category = FindCategory(Tree, i);
            if(category < 0)   // not final tau, do nothing
               continue;

            TauIndex = i;
            break;
         }

         if(category != Category)
            continue;   // skip event
      }

      // calculate MET
      double METWhole[4] = {0, 0, 0, 0};
      double MET[4] = {0, 0, 0, 0};
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // stable particles only
            continue;
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // skip neutrinos
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)
            continue;

         METWhole[1] = METWhole[1] - Tree[i].P[1];
         METWhole[2] = METWhole[2] - Tree[i].P[2];

         double eta = GetEta(Tree[i].P);
         if(eta < 2.4 && eta > -2.4)
         {
            MET[1] = MET[1] - Tree[i].P[1];
            MET[2] = MET[2] - Tree[i].P[2];
         }
      }
      HMETWhole.Fill(GetPT(METWhole));
      HMET.Fill(GetPT(MET));

      // Find jets
      vector<PseudoJet> Tracks = ExtractTracks(Tree, 0.5, ChargedPDGID);
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(Tracks, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      // Jet counts
      int NJet15 = 0;
      int NJet20 = 0;
      int NJet30 = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() > 15)
            NJet15 = NJet15 + 1;
         if(Jets[i].perp() > 20)
            NJet20 = NJet20 + 1;
         if(Jets[i].perp() > 30)
            NJet30 = NJet30 + 1;
      }
      HNJet15.Fill(NJet15);
      HNJet20.Fill(NJet20);
      HNJet30.Fill(NJet30);

      // Jet multiplicity
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() > 15)
            HJetMultiplicity15.Fill(Sequence.constituents(Jets[i]).size());
         if(Jets[i].perp() > 20)
            HJetMultiplicity20.Fill(Sequence.constituents(Jets[i]).size());
         if(Jets[i].perp() > 30)
            HJetMultiplicity30.Fill(Sequence.constituents(Jets[i]).size());
      }

      // 3-track jet minimum radius
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         vector<PseudoJet> Constituents = Sequence.constituents(Jets[i]);
         if(Constituents.size() != 3)
            continue;

         double P1[4] = {Constituents[0].e(), Constituents[0].px(), Constituents[0].py(), Constituents[0].pz()};
         double P2[4] = {Constituents[1].e(), Constituents[1].px(), Constituents[1].py(), Constituents[1].pz()};
         double P3[4] = {Constituents[2].e(), Constituents[2].px(), Constituents[2].py(), Constituents[2].pz()};
         double MinRadius = GetMinRadius(P1, P2, P3);

         HMinRadius3ProngJet.Fill(MinRadius);
         if(Jets[i].perp() > 15)
            HMinRadius3ProngJet15.Fill(MinRadius);
         if(Jets[i].perp() > 20)
            HMinRadius3ProngJet20.Fill(MinRadius);
         if(Jets[i].perp() > 30)
            HMinRadius3ProngJet30.Fill(MinRadius);
      }

      // gen-level tau
      if(ExistTauInEvent == true && TauIndex >= 0)
      {
         double MinDR = 9999999;
         int MinIndex = -1;

         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double JetP[4] = {Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()};

            double DR = GetDR(Tree[TauIndex].P, JetP);

            if(DR < MinDR)
            {
               MinDR = DR;
               MinIndex = i;
            }
         }

         HTauJetDR.Fill(MinDR);
         HTauJetPTRatio.Fill(Jets[MinIndex].perp() / GetPT(Tree[TauIndex].P));
         HTauJetMultiplicity.Fill(Sequence.constituents(Jets[MinIndex]).size());
      }
   }

   PsFile.AddPlot(HMETWhole, "", true);
   PsFile.AddPlot(HMET, "", true);
   PsFile.AddPlot(HNJet15, "hist text00", true);
   PsFile.AddPlot(HNJet20, "hist text00", true);
   PsFile.AddPlot(HNJet30, "hist text00", true);
   PsFile.AddPlot(HTauJetDR, "", true);
   PsFile.AddPlot(HTauJetPTRatio, "", false);
   PsFile.AddPlot(HTauJetMultiplicity, "text00 hist", true);
   PsFile.AddPlot(HJetMultiplicity15, "text00 hist", true);
   PsFile.AddPlot(HJetMultiplicity20, "text00 hist", true);
   PsFile.AddPlot(HJetMultiplicity30, "text00 hist", true);
   PsFile.AddPlot(HMinRadius3ProngJet, "", false);
   PsFile.AddPlot(HMinRadius3ProngJet15, "", false);
   PsFile.AddPlot(HMinRadius3ProngJet20, "", false);
   PsFile.AddPlot(HMinRadius3ProngJet30, "", false);

   in.close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

map<int, int> ReadChargedParticles()
{
   map<int, int> Result;

   ifstream in("ParticleCharge");

   while(in)
   {
      int ID = 0;
      int Charge = 0;

      in >> ID >> Charge;

      if(Charge != 0)
      {
         Result.insert(pair<int, int>(ID, 0));
         Result.insert(pair<int, int>(-ID, 0));   // possible antiparticle
      }
   }

   in.close();

   return Result;
}

vector<PseudoJet> ExtractTracks(GenParticleTree Tree, double PTMin, map<int, int> AllowedPDGList)
{
   vector<PseudoJet> Tracks;

   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].StatusCode != 1)   // not final particle
         continue;

      if(GetPT(Tree[i].P) < PTMin)   // PT too small
         continue;

      if(AllowedPDGList.find(Tree[i].PDGID) == AllowedPDGList.end())   // not in the allowed (charged) list
         continue;

      Tracks.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], GetP(Tree[i].P)));   // massless!
   }

   return Tracks;
}



