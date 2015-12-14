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
#include "GenparticleTree.h"
#include "TauHelperFunctions.h"

int main(int argc, char *argv[]);
void PeekLQDistributions(string InputLQMass = "250");
map<int, int> ReadParticleCharge(string FileName = "ParticleCharge");
int FindFirstIndex(GenParticleTree &Tree, int PDGID, int Status = -1);
double FindPhiPartitionForRazor(vector<GenParticle> &Particles);

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

   string InputLQMass = "250";
   if(argc > 1)
      InputLQMass = argv[1];
   PeekLQDistributions(InputLQMass);

   return 0;
}

void PeekLQDistributions(string InputLQMass)
{
   stringstream ConvertLQMassToDouble(InputLQMass);
   double LQMassValue = 0;
   ConvertLQMassToDouble >> LQMassValue;

   ifstream in(("Samples/LQ" + InputLQMass + "Sample").c_str());

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);
   int NumberOfEvents = Helper.IntValue;

   PsFileHelper PsFile("LQGeneratorLevelDistributions_" + InputLQMass + "GeV.ps");
   PsFile.AddTextPage("LQ3 Generator Level Distributions");

   vector<string> ExplanationText;
   ExplanationText.push_back("Generate samples with CMSSW 3.11.0 (doesn't matter....)");
   ExplanationText.push_back("D6T tune, turning on LQ, force decay to b and nu_tau");
   ExplanationText.push_back("(Following recipe from Dinko and Francesco)");
   ExplanationText.push_back("Input mass: " + InputLQMass + " GeV/c");
   ExplanationText.push_back("");
   ExplanationText.push_back("Jet: anti-kt, R = 0.5, input particle |eta| < 2.4");
   ExplanationText.push_back("All visible refers to all particles that's not neutrinos");
   ExplanationText.push_back("Charged jet = gen jet from charged final particles");
   PsFile.AddTextPage(ExplanationText);

   map<int, int> ParticleCharge = ReadParticleCharge("ParticleCharge");

   TH1D HLQPT("HLQPT", "LQ PT", 100, 0, 1000);
   TH1D HLQP("HLQP", "LQ P", 100, 0, 1000);
   TH1D HLQMass("HLQMass", "LQ Mass", 200, LQMassValue - 2, LQMassValue + 2);
   TH1D HLQEta("HLQEta", "LQ Eta", 100, -5, 5);
   TH1D HLQRapidity("HLQRapidity", "LQ Rapidity", 100, -5, 5);
   TH1D HLQMother("HLQMother", "LQ Mother", 101, -50.5, 50.5);
   TH1D HLQBeta("HLQBeta", "LQ beta", 100, 0, 1);
   TH1D HLQGamma("HLQGamma", "LQ Gamma", 100, 1, 10);
   TH1D HLQTravelLength("HLQTravelLength", "LQ travel length", 100, 0, 100);

   TH1D HLQPairPT("HLQPairPT", "LQPair PT", 100, 0, 1000);
   TH1D HLQPairP("HLQPairP", "LQPair P", 100, 0, 1000);
   TH1D HLQPairMass("HLQPairMass", "LQPair Mass", 100, 0, 2000);
   TH1D HLQPairEta("HLQPairEta", "LQPair Eta", 100, -10, 10);
   TH1D HLQPairRapidity("HLQPairRapidity", "LQPair Rapidity", 100, -5, 5);
   TH1D HLQPairFromQQbarRapidity("HLQPairFromQQbarRapidity", "LQPair (from qqbar) Rapidity", 100, -5, 5);
   TH1D HLQPairAngle("HLQPairAngle", "LQ vs. LQbar opening angle", 100, 0, 3.2);
   TH1D HLQPairBeta("HLQPairBeta", "LQPair beta", 100, 0, 1);
   TH1D HLQPairGamma("HLQPairGamma", "LQPair Gamma", 100, 1, 5);

   TH1D HNuFromLQPT("HNuFromLQPT", "Neutrino (16 or -16) (from LQ) PT", 100, 0, 1000);
   TH1D HNuFromLQP("HNuFromLQP", "Neutrino (16 or -16) (from LQ) P", 100, 0, 1000);
   TH1D HNuFromLQMass("HNuFromLQMass", "Neutrino (16 or -16) (from LQ) Mass", 100, 0, 1);
   TH1D HNuFromLQEta("HNuFromLQEta", "Neutrino (16 or -16) (from LQ) Eta", 100, -5, 5);
   TH1D HNuFromLQRapidity("HNuFromLQRapidity", "Neutrino (16 or -16) (from LQ) Rapidity", 100, -5, 5);
   
   TH1D HNuPairFromLQPT("HNuPairFromLQPT", "(Tau) Neutrino pair from LQ PT", 100, 0, 1000);
   TH1D HNuPairFromLQP("HNuPairFromLQP", "(Tau) Neutrino pair from LQ P", 100, 0, 1000);
   TH1D HNuPairFromLQMass("HNuPairFromLQMass", "(Tau) Neutrino pair from LQ Mass", 100, 0, 1000);
   TH1D HNuPairFromLQEta("HNuPairFromLQEta", "(Tau) Neutrino pair from LQ Eta", 100, -5, 5);
   TH1D HNuPairFromLQRapidity("HNuPairFromLQRapidity", "(Tau) Neutrino pair from LQ Rapidity", 100, -5, 5);
   TH1D HNuPairFromLQAngle("HNuPairFromLQAngle", "(Tau) Neutrino pair from LQ opening Angle", 100, 0, 3.2);

   TH1D HStableNuCount("HStableNuCount", "Stable neutrino (16) count in the event", 10, -0.5, 9.5);
   TH1D HStableNubarCount("HStableNubarCount", "Stable anti-neutrino (-16) count in the event", 10, -0.5, 9.5);
   TH1D HNuCount("HNuCount", "Neutrino (16) count in the event, regardless of status", 10, -0.5, 9.5);
   TH1D HNubarCount("HNubarCount", "Anti-neutrino (-16) count in the event, regardless of status", 10, -0.5, 9.5);
   TH2D HStableNuVsStableNubarCount("HStableNuVsStableNubarCount",
      "Stable nu (16) vs. stable nubar (-16);Stable Nu Count;Stable Nubar Count", 10, -0.5, 9.5, 10, -0.5, 9.5);

   TH1D HBFromLQPT("HBFromLQPT", "b from LQ PT", 100, 0, 1000);
   TH1D HBFromLQP("HBFromLQP", "b from LQ P", 100, 0, 1000);
   TH1D HBFromLQMass("HBFromLQMass", "b from LQ Mass", 100, 4.5, 5);
   TH1D HBFromLQEta("HBFromLQEta", "b from LQ Eta", 100, -5, 5);
   TH1D HBFromLQRapidity("HBFromLQRapidity", "b from LQ Rapidity", 100, -5, 5);
   
   TH1D HBPairFromLQPT("HBPairFromLQPT", "b pair from LQ PT", 100, 0, 1000);
   TH1D HBPairFromLQP("HBPairFromLQP", "b pair from LQ P", 100, 0, 1000);
   TH1D HBPairFromLQMass("HBPairFromLQMass", "b pair from LQ Mass", 100, 0, 1000);
   TH1D HBPairFromLQEta("HBPairFromLQEta", "b pair from LQ Eta", 100, -5, 5);
   TH1D HBPairFromLQRapidity("HBPairFromLQRapidity", "b pair from LQ Rapidity", 100, -5, 5);
   TH1D HBPairFromLQAngle("HBPairFromLQAngle", "b pair from LQ Angle", 100, 0, 3.2);
   TH2D HBPTVsBPTFromLQ("HBPTVsBPTFromLQ", "b from LQ vs. b from LQbar;b PT from LQ;b PT from LQbar",
      100, 0, 500, 100, 0, 500);

   TH1D HNJet15("HNJet15", "Number of jets above 15 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNJet30("HNJet30", "Number of jets above 30 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNJet50("HNJet50", "Number of jets above 50 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNJet100("HNJet100", "Number of jets above 100 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNJet150("HNJet150", "Number of jets above 150 GeV (PT)", 10, -0.5, 9.5);
   TH1D HLeadingJetPT("HLeadingJetPT", "Leading jet PT", 100, 0, 1000);
   TH1D HLeadingJetEta("HLeadingJetEta", "Leading jet eta", 100, -3, 3);
   TH1D HLeadingJetMultiplicity("HLeadingJetMultiplicity", "Leading jet multiplicity", 40, -0.5, 39.5);
   
   TH1D HNChargedJet15("HNChargedJet15", "Number of charged jets above 15 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNChargedJet30("HNChargedJet30", "Number of charged jets above 30 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNChargedJet50("HNChargedJet50", "Number of charged jets above 50 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNChargedJet100("HNChargedJet100", "Number of charged jets above 100 GeV (PT)", 10, -0.5, 9.5);
   TH1D HNChargedJet150("HNChargedJet150", "Number of charged jets above 150 GeV (PT)", 10, -0.5, 9.5);
   TH1D HLeadingChargedJetPT("HLeadingChargedJetPT", "Leading charged jet PT", 100, 0, 1000);
   TH1D HLeadingChargedJetEta("HLeadingChargedJetEta", "Leading charged jet eta", 100, -3, 3);
   TH1D HLeadingChargedJetMultiplicity("HLeadingChargedJetMultiplicity",
      "Leading charged jet multiplicity", 40, -0.5, 39.5);

   TH1D HBFromLQClosestJetAngle("HBFromLQClosestJetAngle",
      "b (eta < 2.4) vs. closest gen-jet angle", 100, 0, 1.5);
   TH1D HBFromLQClosestJetDR("HBFromLQClosestJetDR",
      "b (eta < 2.4) vs. closest gen-jet dR", 100, 0, 3.2);
   TH1D HBFromLQClosestJetDPhi("HBFromLQClosestJetDPhi",
      "b (eta < 2.4) vs. closest gen-jet delta phi", 100, -3.2, 3.2);
   TH1D HBFromLQClosestJetPTRatio("HBFromLQClosestJetPTRatio",
      "b (eta < 2.4) vs. closest gen-jet PT ratio;Jet PT/b PT", 100, 0, 1.5);
   TH1D HBFromLQClosestJetMultiplicity("HBFromLQClosestJetMultiplicity",
      "closest gen-jet to b (from LQ, eta < 2.4) multiplicity", 40, -0.5, 39.5);
   
   TH1D HBFromLQClosestChargedJetAngle("HBFromLQClosestChargedJetAngle",
      "b (eta < 2.4) vs. closest charged jet angle", 100, 0, 1.5);
   TH1D HBFromLQClosestChargedJetDR("HBFromLQClosestChargedJetDR",
      "b (eta < 2.4) vs. closest charged jet dR", 100, 0, 3.2);
   TH1D HBFromLQClosestChargedJetDPhi("HBFromLQClosestChargedJetDPhi",
      "b (eta < 2.4) vs. closest charged jet delta phi", 100, -3.2, 3.2);
   TH1D HBFromLQClosestChargedJetPTRatio("HBFromLQClosestChargedJetPTRatio",
      "b (eta < 2.4) vs. closest charged jet PT ratio;Jet PT/b PT", 100, 0, 1.5);
   TH1D HBFromLQClosestChargedJetMultiplicity("HBFromLQClosestChargedJetMultiplicity",
      "closest charged jet to b (from LQ, eta < 2.4) multiplicity", 40, -0.5, 39.5);

   TH1D HVisibleMR("HVisibleMR", "Visible MR distribution", 100, 0, 2000);
   TH1D HVisibleMRT("HVisibleMRT", "Visible MRT distribution", 100, 0, 2000);
   TH1D HVisibleR("HVisibleR", "Visible R distribution", 100, 0, 1);
   TH2D HVisibleMRVsR("HVisibleMRVsR", "Visible MR vs. R;MR;R", 100, 0, 2000, 100, 0, 1);
   
   TH1D HLeadingJetsMR("HLeadingJetsMR", "Leading jets MR distribution", 100, 0, 1000);
   TH1D HLeadingJetsMRT("HLeadingJetsMRT", "Leading jets MRT distribution", 100, 0, 1000);
   TH1D HLeadingJetsR("HLeadingJetsR", "Leading jets R distribution", 100, 0, 1);
   TH2D HLeadingJetsMRVsR("HLeadingJetsMRVsR", "Leading jets MR vs. R;MR;R", 100, 0, 1000, 100, 0, 1);

   TH1D HLeadingJetsSmearedMR("HLeadingJetsSmearedMR", "Leading jets smeared MR distribution", 100, 0, 1000);
   TH1D HLeadingJetsSmearedMRT("HLeadingJetsSmearedMRT", "Leading jets smeared MRT distribution", 100, 0, 1000);
   TH1D HLeadingJetsSmearedR("HLeadingJetsSmearedR", "Leading jets R smeared distribution", 100, 0, 1);
   TH2D HLeadingJetsSmearedMRVsR("HLeadingJetsSmearedMRVsR", "Leading jets smeared MR vs. R;MR;R",
      100, 0, 1000, 100, 0, 1);

   TH1D HLeadingChargedJetsMR("HLeadingChargedJetsMR", "Leading charged jets MR distribution", 100, 0, 1000);
   TH1D HLeadingChargedJetsMRT("HLeadingChargedJetsMRT", "Leading charged jets MRT distribution", 100, 0, 1000);
   TH1D HLeadingChargedJetsR("HLeadingChargedJetsR", "Leading charged jets R distribution", 100, 0, 1);
   TH2D HLeadingChargedJetsMRVsR("HLeadingChargedJetsMRVsR", "Leading charged jets MR vs. R;MR;R",
      100, 0, 1000, 100, 0, 1);

   TH1D HBFromLQMR("HBFromLQMR", "MR distribution from LQ b quarks", 100, 0, 1000);
   TH1D HBFromLQMRT("HBFromLQMRT", "MRT distribution from LQ b quarks", 100, 0, 1000);
   TH1D HBFromLQR("HBFromLQR", "R distribution from LQ b quarks", 100, 0, 1);
   TH2D HBFromLQMRVsR("HBFromLQMRVsR", "MR vs. R from LQ b quarks;MR;R", 100, 0, 1000, 100, 0, 1);

   for(int iEvent = 0; iEvent < NumberOfEvents; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEvents << endl;

      GenParticleTree Tree;
      Tree.LoadFromStream(in, false);

      int LQIndex = FindFirstIndex(Tree, 42);
      int LQbarIndex = FindFirstIndex(Tree, -42);
      int NuFromLQIndex = -1;
      int NuFromLQbarIndex = -1;
      int BFromLQIndex = -1;
      int BFromLQbarIndex = -1;

      if(LQIndex >= 0)
      {
         for(int i = 0; i < (int)Tree[LQIndex].Daughters.size(); i++)
         {
            int Index = Tree[LQIndex].Daughters[i];
            if(Tree[Index].PDGID == 16 || Tree[Index].PDGID == -16)   // nu_tau
            {
               NuFromLQIndex = Index;
               break;
            }
         }
         for(int i = 0; i < (int)Tree[LQIndex].Daughters.size(); i++)
         {
            int Index = Tree[LQIndex].Daughters[i];
            if(Tree[Index].PDGID == 5 || Tree[Index].PDGID == -5)   // b quark
            {
               BFromLQIndex = Index;
               break;
            }
         }
      }

      // Make jets
      vector<PseudoJet> VisibleParticles;
      vector<PseudoJet> VisibleChargedParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // not final
            continue;
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // neutrino
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)   // neutrino
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)   // neutrino
            continue;
         if(fabs(GetEta(Tree[i].P)) > 2.4)   // outside reach
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));

         if(ParticleCharge.find(Tree[i].PDGID) != ParticleCharge.end() && ParticleCharge[Tree[i].PDGID] != 0)
            VisibleChargedParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);
      ClusterSequence ChargedSequence(VisibleChargedParticles, Definition);
      vector<PseudoJet> ChargedJets = ChargedSequence.inclusive_jets(0.5);

      // Smeared jets
      vector<PseudoJet> SmearedJets;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         double Factor = DrawGaussian(1, 0.2);
         SmearedJets.push_back(PseudoJet(Jets[i].px() * Factor, Jets[i].py() * Factor,
            Jets[i].pz() * Factor, Jets[i].e() * Factor));
      }
      
      // find nu and b indices
      if(LQbarIndex >= 0)
      {
         for(int i = 0; i < (int)Tree[LQbarIndex].Daughters.size(); i++)
         {
            int Index = Tree[LQbarIndex].Daughters[i];
            if(Tree[Index].PDGID == 16 || Tree[Index].PDGID == -16)   // tau neutrino
            {
               NuFromLQbarIndex = Index;
               break;
            }
         }
         for(int i = 0; i < (int)Tree[LQbarIndex].Daughters.size(); i++)
         {
            int Index = Tree[LQbarIndex].Daughters[i];
            if(Tree[Index].PDGID == 5 || Tree[Index].PDGID == -5)   // b
            {
               BFromLQbarIndex = Index;
               break;
            }
         }
      }

      // LQ Distributions
      if(LQIndex >= 0)
      {
         HLQPT.Fill(GetPT(Tree[LQIndex].P));
         HLQP.Fill(GetP(Tree[LQIndex].P));
         HLQMass.Fill(GetMass(Tree[LQIndex].P));
         HLQEta.Fill(GetEta(Tree[LQIndex].P));
         HLQRapidity.Fill(GetRapidity(Tree[LQIndex].P));
         for(int i = 0; i < Tree[LQIndex].Mothers.size(); i++)
            HLQMother.Fill(Tree[Tree[LQIndex].Mothers[i]].PDGID);
         HLQBeta.Fill(GetBeta(Tree[LQIndex].P));
         HLQGamma.Fill(GetGamma(Tree[LQIndex].P));

         if(Tree[LQIndex].Daughters.size() > 0)
         {
            double *V0 = Tree[LQIndex].V;
            double *V1 = Tree[Tree[LQIndex].Daughters[0]].V;
            double DV[4] = {V0[0] - V1[0], V0[1] - V1[1], V0[2] - V1[2], V0[3] - V1[3]};
            HLQTravelLength.Fill(GetP(DV));
         }
      }

      // LQbar Distributions
      if(LQbarIndex >= 0)
      {
         HLQPT.Fill(GetPT(Tree[LQbarIndex].P));
         HLQP.Fill(GetP(Tree[LQbarIndex].P));
         HLQMass.Fill(GetMass(Tree[LQbarIndex].P));
         HLQEta.Fill(GetEta(Tree[LQbarIndex].P));
         HLQRapidity.Fill(GetRapidity(Tree[LQbarIndex].P));
         for(int i = 0; i < Tree[LQbarIndex].Mothers.size(); i++)
            HLQMother.Fill(Tree[Tree[LQbarIndex].Mothers[i]].PDGID);
         HLQBeta.Fill(GetBeta(Tree[LQbarIndex].P));
         HLQGamma.Fill(GetGamma(Tree[LQbarIndex].P));
         
         if(Tree[LQbarIndex].Daughters.size() > 0)
         {
            double *V0 = Tree[LQbarIndex].V;
            double *V1 = Tree[Tree[LQbarIndex].Daughters[0]].V;
            double DV[4] = {V0[0] - V1[0], V0[1] - V1[1], V0[2] - V1[2], V0[3] - V1[3]};
            HLQTravelLength.Fill(GetP(DV));
         }
      }

      // LQ Pair
      if(LQIndex >= 0 && LQbarIndex >= 0)
      {
         double LQPairP[4] = {0, 0, 0, 0};
         LQPairP[0] = Tree[LQIndex].P[0] + Tree[LQbarIndex].P[0];
         LQPairP[1] = Tree[LQIndex].P[1] + Tree[LQbarIndex].P[1];
         LQPairP[2] = Tree[LQIndex].P[2] + Tree[LQbarIndex].P[2];
         LQPairP[3] = Tree[LQIndex].P[3] + Tree[LQbarIndex].P[3];

         HLQPairPT.Fill(GetPT(LQPairP));
         HLQPairP.Fill(GetP(LQPairP));
         HLQPairMass.Fill(GetMass(LQPairP));
         HLQPairEta.Fill(GetEta(LQPairP));
         HLQPairRapidity.Fill(GetRapidity(LQPairP));
         if(Tree[LQIndex].Mothers.size() > 0 && abs(Tree[Tree[LQIndex].Mothers[0]].PDGID) <= 6)
            HLQPairFromQQbarRapidity.Fill(GetRapidity(LQPairP));
         HLQPairAngle.Fill(GetAngle(Tree[LQIndex].P, Tree[LQbarIndex].P));
         HLQPairBeta.Fill(GetBeta(LQPairP));
         HLQPairGamma.Fill(GetGamma(LQPairP));
      }

      // Nu from LQ
      if(NuFromLQIndex >= 0)
      {
         HNuFromLQPT.Fill(GetPT(Tree[NuFromLQIndex].P));
         HNuFromLQP.Fill(GetP(Tree[NuFromLQIndex].P));
         HNuFromLQMass.Fill(GetMass(Tree[NuFromLQIndex].P));
         HNuFromLQEta.Fill(GetEta(Tree[NuFromLQIndex].P));
         HNuFromLQRapidity.Fill(GetRapidity(Tree[NuFromLQIndex].P));
      }

      // Nu from LQbar
      if(NuFromLQbarIndex >= 0)
      {
         HNuFromLQPT.Fill(GetPT(Tree[NuFromLQbarIndex].P));
         HNuFromLQP.Fill(GetP(Tree[NuFromLQbarIndex].P));
         HNuFromLQMass.Fill(GetMass(Tree[NuFromLQbarIndex].P));
         HNuFromLQEta.Fill(GetEta(Tree[NuFromLQbarIndex].P));
         HNuFromLQRapidity.Fill(GetRapidity(Tree[NuFromLQbarIndex].P));
      }

      // Neutrino pair from LQ
      if(NuFromLQIndex >= 0 && NuFromLQbarIndex >= 0)
      {
         double NuPairP[4] = {0};
         NuPairP[0] = Tree[NuFromLQIndex].P[0] + Tree[NuFromLQbarIndex].P[0];
         NuPairP[1] = Tree[NuFromLQIndex].P[1] + Tree[NuFromLQbarIndex].P[1];
         NuPairP[2] = Tree[NuFromLQIndex].P[2] + Tree[NuFromLQbarIndex].P[2];
         NuPairP[3] = Tree[NuFromLQIndex].P[3] + Tree[NuFromLQbarIndex].P[3];

         HNuPairFromLQPT.Fill(GetPT(NuPairP));
         HNuPairFromLQP.Fill(GetP(NuPairP));
         HNuPairFromLQEta.Fill(GetEta(NuPairP));
         HNuPairFromLQRapidity.Fill(GetRapidity(NuPairP));
         HNuPairFromLQMass.Fill(GetMass(NuPairP));
         HNuPairFromLQAngle.Fill(GetAngle(Tree[NuFromLQIndex].P, Tree[NuFromLQbarIndex].P));
      }
      
      // event-wise neutrino distributions
      int StableNuCount = 0;
      int StableNubarCount = 0;
      int NuCount = 0;
      int NubarCount = 0;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].PDGID == 16 && Tree[i].StatusCode == 1)
            StableNuCount = StableNuCount + 1;
         if(Tree[i].PDGID == -16 && Tree[i].StatusCode == 1)
            StableNubarCount = StableNubarCount + 1;
         if(Tree[i].PDGID == 16)
            NuCount = NuCount + 1;
         if(Tree[i].PDGID == -16)
            NubarCount = NubarCount + 1;
      }

      HStableNuCount.Fill(StableNuCount);
      HStableNubarCount.Fill(StableNubarCount);
      HNuCount.Fill(NuCount);
      HNubarCount.Fill(NubarCount);
      HStableNuVsStableNubarCount.Fill(StableNuCount, StableNubarCount);

      // b from LQ distributions
      if(BFromLQIndex >= 0)
      {
         HBFromLQPT.Fill(GetPT(Tree[BFromLQIndex].P));
         HBFromLQP.Fill(GetP(Tree[BFromLQIndex].P));
         HBFromLQMass.Fill(GetMass(Tree[BFromLQIndex].P));
         HBFromLQEta.Fill(GetEta(Tree[BFromLQIndex].P));
         HBFromLQRapidity.Fill(GetRapidity(Tree[BFromLQIndex].P));
      }
      
      // b from LQbar distributions
      if(BFromLQbarIndex >= 0)
      {
         HBFromLQPT.Fill(GetPT(Tree[BFromLQbarIndex].P));
         HBFromLQP.Fill(GetP(Tree[BFromLQbarIndex].P));
         HBFromLQMass.Fill(GetMass(Tree[BFromLQbarIndex].P));
         HBFromLQEta.Fill(GetEta(Tree[BFromLQbarIndex].P));
         HBFromLQRapidity.Fill(GetRapidity(Tree[BFromLQbarIndex].P));
      }

      // b pair from LQ distributions
      if(BFromLQIndex >= 0 && BFromLQbarIndex >= 0)
      {
         double BPairP[4] = {0};
         BPairP[0] = Tree[BFromLQIndex].P[0] + Tree[BFromLQbarIndex].P[0];
         BPairP[1] = Tree[BFromLQIndex].P[1] + Tree[BFromLQbarIndex].P[1];
         BPairP[2] = Tree[BFromLQIndex].P[2] + Tree[BFromLQbarIndex].P[2];
         BPairP[3] = Tree[BFromLQIndex].P[3] + Tree[BFromLQbarIndex].P[3];

         HBPairFromLQPT.Fill(GetPT(BPairP));
         HBPairFromLQP.Fill(GetP(BPairP));
         HBPairFromLQEta.Fill(GetEta(BPairP));
         HBPairFromLQRapidity.Fill(GetRapidity(BPairP));
         HBPairFromLQMass.Fill(GetMass(BPairP));
         HBPairFromLQAngle.Fill(GetAngle(Tree[BFromLQIndex].P, Tree[BFromLQbarIndex].P));
         HBPTVsBPTFromLQ.Fill(GetPT(Tree[BFromLQIndex].P), GetPT(Tree[BFromLQbarIndex].P));
      }

      // Jet Counts
      int NJet15 = 0;
      int NJet30 = 0;
      int NJet50 = 0;
      int NJet100 = 0;
      int NJet150 = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() > 15)   NJet15 = NJet15 + 1;
         if(Jets[i].perp() > 30)   NJet30 = NJet30 + 1;
         if(Jets[i].perp() > 50)   NJet50 = NJet50 + 1;
         if(Jets[i].perp() > 100)   NJet100 = NJet100 + 1;
         if(Jets[i].perp() > 150)   NJet150 = NJet150 + 1;
      }
      HNJet15.Fill(NJet15);
      HNJet30.Fill(NJet30);
      HNJet50.Fill(NJet50);
      HNJet100.Fill(NJet100);
      HNJet150.Fill(NJet150);
     
      // Leading Jet
      int LeadingJetIndex = -1;
      for(int i = 0; i < (int)Jets.size(); i++)
         if(Jets[i].perp() > Jets[LeadingJetIndex].perp())
            LeadingJetIndex = i;
      if(LeadingJetIndex >= 0)
      {
         double LeadingJetP[4] = {Jets[LeadingJetIndex].e(), Jets[LeadingJetIndex].px(),
            Jets[LeadingJetIndex].py(), Jets[LeadingJetIndex].pz()};
         HLeadingJetPT.Fill(GetPT(LeadingJetP));
         HLeadingJetEta.Fill(GetEta(LeadingJetP));
         HLeadingJetMultiplicity.Fill(Sequence.constituents(Jets[LeadingJetIndex]).size());
      }

      // Sub-leading jet
      int SubLeadingJetIndex = -1;
      if(Jets.size() >= 2)
      {
         SubLeadingJetIndex = 0;
         if(LeadingJetIndex == 0)
            SubLeadingJetIndex = 1;

         for(int i = 0; i < (int)Jets.size(); i++)
         {
            if(i == LeadingJetIndex)
               continue;

            if(Jets[i].perp() > Jets[SubLeadingJetIndex].perp())
               SubLeadingJetIndex = i;
         }
      }

      // leading and sub-leading jets from the smeared collection
      int LeadingSmearedJetIndex = -1;
      for(int i = 0; i < (int)SmearedJets.size(); i++)
         if(SmearedJets[i].perp() > SmearedJets[LeadingSmearedJetIndex].perp())
            LeadingSmearedJetIndex = i;
      
      int SubLeadingSmearedJetIndex = -1;
      if(SmearedJets.size() >= 2)
      {
         SubLeadingSmearedJetIndex = 0;
         if(LeadingSmearedJetIndex == 0)
            SubLeadingSmearedJetIndex = 1;

         for(int i = 0; i < (int)SmearedJets.size(); i++)
         {
            if(i == LeadingSmearedJetIndex)
               continue;

            if(SmearedJets[i].perp() > SmearedJets[SubLeadingSmearedJetIndex].perp())
               SubLeadingSmearedJetIndex = i;
         }
      }

      // Charged jet counts
      int NChargedJet15 = 0;
      int NChargedJet30 = 0;
      int NChargedJet50 = 0;
      int NChargedJet100 = 0;
      int NChargedJet150 = 0;
      for(int i = 0; i < (int)ChargedJets.size(); i++)
      {
         if(ChargedJets[i].perp() > 15)   NChargedJet15 = NChargedJet15 + 1;
         if(ChargedJets[i].perp() > 30)   NChargedJet30 = NChargedJet30 + 1;
         if(ChargedJets[i].perp() > 50)   NChargedJet50 = NChargedJet50 + 1;
         if(ChargedJets[i].perp() > 100)   NChargedJet100 = NChargedJet100 + 1;
         if(ChargedJets[i].perp() > 150)   NChargedJet150 = NChargedJet150 + 1;
      }
      HNChargedJet15.Fill(NChargedJet15);
      HNChargedJet30.Fill(NChargedJet30);
      HNChargedJet50.Fill(NChargedJet50);
      HNChargedJet100.Fill(NChargedJet100);
      HNChargedJet150.Fill(NChargedJet150);
      
      // Leading Charged Jet
      int LeadingChargedJetIndex = -1;
      for(int i = 0; i < (int)ChargedJets.size(); i++)
         if(ChargedJets[i].perp() > ChargedJets[LeadingChargedJetIndex].perp())
            LeadingChargedJetIndex = i;
      if(LeadingChargedJetIndex >= 0)
      {
         double LeadingChargedJetP[4] = {ChargedJets[LeadingChargedJetIndex].e(),
            ChargedJets[LeadingChargedJetIndex].px(),
            ChargedJets[LeadingChargedJetIndex].py(),
            ChargedJets[LeadingChargedJetIndex].pz()};
         HLeadingChargedJetPT.Fill(GetPT(LeadingChargedJetP));
         HLeadingChargedJetEta.Fill(GetEta(LeadingChargedJetP));
         HLeadingChargedJetMultiplicity.Fill(ChargedSequence.constituents(ChargedJets[LeadingChargedJetIndex]).size());
      }

      // Sub-leading Charged Jet
      int SubLeadingChargedJetIndex = -1;
      if(ChargedJets.size() >= 2)
      {
         SubLeadingChargedJetIndex = 0;
         if(LeadingChargedJetIndex == 0)
            SubLeadingChargedJetIndex = 1;

         for(int i = 0; i < (int)ChargedJets.size(); i++)
         {
            if(i == LeadingChargedJetIndex)
               continue;

            if(ChargedJets[i].perp() > ChargedJets[SubLeadingChargedJetIndex].perp())
               SubLeadingChargedJetIndex = i;
         }
      }

      // closest jet to b from LQ
      int ClosestJetToBFromLQIndex = -1;
      int ClosestJetToBFromLQbarIndex = -1;
      double ClosestJetToBFromLQP[4] = {0};
      double ClosestJetToBFromLQbarP[4] = {0};
      if(BFromLQIndex >= 0)
      {
         double MinDR = 99999999;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double JetP[4] = {Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()};
            double DR = GetDR(JetP, Tree[BFromLQIndex].P);
            if(MinDR > DR)
            {
               MinDR = DR;
               ClosestJetToBFromLQIndex = i;

               ClosestJetToBFromLQP[0] = JetP[0];
               ClosestJetToBFromLQP[1] = JetP[1];
               ClosestJetToBFromLQP[2] = JetP[2];
               ClosestJetToBFromLQP[3] = JetP[3];
            }
         }
      }
      if(BFromLQbarIndex >= 0)
      {
         double MinDR = 99999999;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double JetP[4] = {Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()};
            double DR = GetDR(JetP, Tree[BFromLQbarIndex].P);
            if(MinDR > DR)
            {
               MinDR = DR;
               ClosestJetToBFromLQbarIndex = i;
               
               ClosestJetToBFromLQbarP[0] = JetP[0];
               ClosestJetToBFromLQbarP[1] = JetP[1];
               ClosestJetToBFromLQbarP[2] = JetP[2];
               ClosestJetToBFromLQbarP[3] = JetP[3];
            }
         }
      }

      if(ClosestJetToBFromLQIndex >= 0 && BFromLQIndex >= 0 && fabs(GetEta(Tree[BFromLQIndex].P)) < 2.4)
      {
         HBFromLQClosestJetAngle.Fill(GetAngle(ClosestJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestJetDR.Fill(GetDR(ClosestJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestJetDPhi.Fill(GetDPhi(ClosestJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestJetPTRatio.Fill(GetPT(ClosestJetToBFromLQP) / GetPT(Tree[BFromLQIndex].P));
         
         int Multiplicity = Sequence.constituents(Jets[ClosestJetToBFromLQIndex]).size();
         HBFromLQClosestJetMultiplicity.Fill(Multiplicity);
      }
      if(ClosestJetToBFromLQbarIndex >= 0 && BFromLQbarIndex >= 0 && fabs(GetEta(Tree[BFromLQbarIndex].P)) < 2.4)
      {
         HBFromLQClosestJetAngle.Fill(GetAngle(ClosestJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestJetDR.Fill(GetDR(ClosestJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestJetDPhi.Fill(GetDPhi(ClosestJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestJetPTRatio.Fill(GetPT(ClosestJetToBFromLQbarP) / GetPT(Tree[BFromLQbarIndex].P));
         
         int Multiplicity = Sequence.constituents(Jets[ClosestJetToBFromLQbarIndex]).size();
         HBFromLQClosestJetMultiplicity.Fill(Multiplicity);
      }
      
      // closest charged jet to b from LQ
      int ClosestChargedJetToBFromLQIndex = -1;
      int ClosestChargedJetToBFromLQbarIndex = -1;
      double ClosestChargedJetToBFromLQP[4] = {0};
      double ClosestChargedJetToBFromLQbarP[4] = {0};
      if(BFromLQIndex >= 0)
      {
         double MinDR = 99999999;
         for(int i = 0; i < (int)ChargedJets.size(); i++)
         {
            double JetP[4] = {ChargedJets[i].e(), ChargedJets[i].px(), ChargedJets[i].py(), ChargedJets[i].pz()};
            double DR = GetDR(JetP, Tree[BFromLQIndex].P);
            if(MinDR > DR)
            {
               MinDR = DR;
               ClosestChargedJetToBFromLQIndex = i;

               ClosestChargedJetToBFromLQP[0] = JetP[0];
               ClosestChargedJetToBFromLQP[1] = JetP[1];
               ClosestChargedJetToBFromLQP[2] = JetP[2];
               ClosestChargedJetToBFromLQP[3] = JetP[3];
            }
         }
      }
      if(BFromLQbarIndex >= 0)
      {
         double MinDR = 99999999;
         for(int i = 0; i < (int)ChargedJets.size(); i++)
         {
            double JetP[4] = {ChargedJets[i].e(), ChargedJets[i].px(), ChargedJets[i].py(), ChargedJets[i].pz()};
            double DR = GetDR(JetP, Tree[BFromLQbarIndex].P);
            if(MinDR > DR)
            {
               MinDR = DR;
               ClosestChargedJetToBFromLQbarIndex = i;
               
               ClosestChargedJetToBFromLQbarP[0] = JetP[0];
               ClosestChargedJetToBFromLQbarP[1] = JetP[1];
               ClosestChargedJetToBFromLQbarP[2] = JetP[2];
               ClosestChargedJetToBFromLQbarP[3] = JetP[3];
            }
         }
      }

      if(ClosestChargedJetToBFromLQIndex >= 0 && BFromLQIndex >= 0 && fabs(GetEta(Tree[BFromLQIndex].P)) < 2.4)
      {
         HBFromLQClosestChargedJetAngle.Fill(GetAngle(ClosestChargedJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestChargedJetDR.Fill(GetDR(ClosestChargedJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestChargedJetDPhi.Fill(GetDPhi(ClosestChargedJetToBFromLQP, Tree[BFromLQIndex].P));
         HBFromLQClosestChargedJetPTRatio.Fill(GetPT(ClosestChargedJetToBFromLQP) / GetPT(Tree[BFromLQIndex].P));
         
         int Multiplicity = ChargedSequence.constituents(ChargedJets[ClosestChargedJetToBFromLQIndex]).size();
         HBFromLQClosestChargedJetMultiplicity.Fill(Multiplicity);
      }
      if(ClosestChargedJetToBFromLQbarIndex >= 0 && BFromLQbarIndex >= 0
         && fabs(GetEta(Tree[BFromLQbarIndex].P)) < 2.4)
      {
         HBFromLQClosestChargedJetAngle.Fill(GetAngle(ClosestChargedJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestChargedJetDR.Fill(GetDR(ClosestChargedJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestChargedJetDPhi.Fill(GetDPhi(ClosestChargedJetToBFromLQbarP, Tree[BFromLQbarIndex].P));
         HBFromLQClosestChargedJetPTRatio.Fill(GetPT(ClosestChargedJetToBFromLQbarP)
            / GetPT(Tree[BFromLQbarIndex].P));

         int Multiplicity = ChargedSequence.constituents(ChargedJets[ClosestChargedJetToBFromLQbarIndex]).size();
         HBFromLQClosestChargedJetMultiplicity.Fill(Multiplicity);
      }

      // R and MR
      vector<GenParticle> VisibleFinalParticles;
      for(int i = 0; i < (int)Tree.ParticleCount(); i++)
      {
         // visible, within eta 2.4, final
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

         VisibleFinalParticles.push_back(Tree[i]);
      }

      double PhiPartition = FindPhiPartitionForRazor(VisibleFinalParticles);
      double VisibleFinalP1[4] = {0};
      double VisibleFinalP2[4] = {0};
      double VisibleFinalTotalP[4] = {0};
      for(int i = 0; i < (int)VisibleFinalParticles.size(); i++)
      {
         double Phi = GetPhi(VisibleFinalParticles[i].P);
         if(PhiPartition <= Phi && Phi < PhiPartition + PI)
         {
            VisibleFinalP1[0] = VisibleFinalP1[0] + VisibleFinalParticles[i].P[0];
            VisibleFinalP1[1] = VisibleFinalP1[1] + VisibleFinalParticles[i].P[1];
            VisibleFinalP1[2] = VisibleFinalP1[2] + VisibleFinalParticles[i].P[2];
            VisibleFinalP1[3] = VisibleFinalP1[3] + VisibleFinalParticles[i].P[3];
         }
         else
         {
            VisibleFinalP2[0] = VisibleFinalP2[0] + VisibleFinalParticles[i].P[0];
            VisibleFinalP2[1] = VisibleFinalP2[1] + VisibleFinalParticles[i].P[1];
            VisibleFinalP2[2] = VisibleFinalP2[2] + VisibleFinalParticles[i].P[2];
            VisibleFinalP2[3] = VisibleFinalP2[3] + VisibleFinalParticles[i].P[3];
         }
      }

      VisibleFinalTotalP[0] = VisibleFinalP1[0] + VisibleFinalP2[0];
      VisibleFinalTotalP[1] = VisibleFinalP1[1] + VisibleFinalP2[1];
      VisibleFinalTotalP[2] = VisibleFinalP1[2] + VisibleFinalP2[2];
      VisibleFinalTotalP[3] = VisibleFinalP1[3] + VisibleFinalP2[3];

      double VisibleFinalME[4] = {0, 0, 0, 0};
      VisibleFinalME[0] = GetPT(VisibleFinalTotalP);
      VisibleFinalME[1] = -VisibleFinalTotalP[1];
      VisibleFinalME[2] = -VisibleFinalTotalP[2];
      VisibleFinalME[3] = 0;

      double VisibleFinalMR = GetMR(VisibleFinalP1, VisibleFinalP2);
      double VisibleFinalMRT = GetMRT(VisibleFinalP1, VisibleFinalP2, VisibleFinalME);
      double VisibleFinalR = GetR(VisibleFinalP1, VisibleFinalP2, VisibleFinalME);

      HVisibleMR.Fill(VisibleFinalMR);
      HVisibleMRT.Fill(VisibleFinalMRT);
      HVisibleR.Fill(VisibleFinalR);
      HVisibleMRVsR.Fill(VisibleFinalMR, VisibleFinalR);

      // MR and R from 2 leading jets
      if(LeadingJetIndex >= 0 && SubLeadingJetIndex >= 0)
      {
         double LeadingJetP[4] = {Jets[LeadingJetIndex].e(), Jets[LeadingJetIndex].px(),
            Jets[LeadingJetIndex].py(), Jets[LeadingJetIndex].pz()};
         double SubLeadingJetP[4] = {Jets[SubLeadingJetIndex].e(), Jets[SubLeadingJetIndex].px(),
            Jets[SubLeadingJetIndex].py(), Jets[SubLeadingJetIndex].pz()};

         double LeadingJetMR = GetMR(LeadingJetP, SubLeadingJetP);
         double LeadingJetMRT = GetMRT(LeadingJetP, SubLeadingJetP, VisibleFinalME);
         double LeadingJetR = GetR(LeadingJetP, SubLeadingJetP, VisibleFinalME);

         HLeadingJetsMR.Fill(LeadingJetMR);
         HLeadingJetsMRT.Fill(LeadingJetMRT);
         HLeadingJetsR.Fill(LeadingJetR);
         HLeadingJetsMRVsR.Fill(LeadingJetMR, LeadingJetR);
      }
      
      // MR and R from 2 leading jets (smeared)
      if(LeadingSmearedJetIndex >= 0 && SubLeadingSmearedJetIndex >= 0)
      {
         double LeadingSmearedJetP[4] = {SmearedJets[LeadingSmearedJetIndex].e(),
            SmearedJets[LeadingSmearedJetIndex].px(),
            SmearedJets[LeadingSmearedJetIndex].py(),
            SmearedJets[LeadingSmearedJetIndex].pz()};
         double SubLeadingSmearedJetP[4] = {SmearedJets[SubLeadingSmearedJetIndex].e(),
            SmearedJets[SubLeadingSmearedJetIndex].px(),
            SmearedJets[SubLeadingSmearedJetIndex].py(),
            SmearedJets[SubLeadingSmearedJetIndex].pz()};

         double LeadingSmearedJetMR = GetMR(LeadingSmearedJetP, SubLeadingSmearedJetP);
         double LeadingSmearedJetMRT = GetMRT(LeadingSmearedJetP, SubLeadingSmearedJetP, VisibleFinalME);
         double LeadingSmearedJetR = GetR(LeadingSmearedJetP, SubLeadingSmearedJetP, VisibleFinalME);

         HLeadingJetsSmearedMR.Fill(LeadingSmearedJetMR);
         HLeadingJetsSmearedMRT.Fill(LeadingSmearedJetMRT);
         HLeadingJetsSmearedR.Fill(LeadingSmearedJetR);
         HLeadingJetsSmearedMRVsR.Fill(LeadingSmearedJetMR, LeadingSmearedJetR);
      }
      
      // MR and R from 2 leading charged jets
      if(LeadingChargedJetIndex >= 0 && SubLeadingChargedJetIndex >= 0)
      {
         double LeadingChargedJetP[4] = {ChargedJets[LeadingChargedJetIndex].e(),
            ChargedJets[LeadingChargedJetIndex].px(),
            ChargedJets[LeadingChargedJetIndex].py(),
            ChargedJets[LeadingChargedJetIndex].pz()};
         double SubLeadingChargedJetP[4] = {ChargedJets[SubLeadingJetIndex].e(),
            ChargedJets[SubLeadingChargedJetIndex].px(),
            ChargedJets[SubLeadingChargedJetIndex].py(),
            ChargedJets[SubLeadingChargedJetIndex].pz()};

         double LeadingChargedJetMR = GetMR(LeadingChargedJetP, SubLeadingChargedJetP);
         double LeadingChargedJetMRT = GetMRT(LeadingChargedJetP, SubLeadingChargedJetP, VisibleFinalME);
         double LeadingChargedJetR = GetR(LeadingChargedJetP, SubLeadingChargedJetP, VisibleFinalME);

         HLeadingChargedJetsMR.Fill(LeadingChargedJetMR);
         HLeadingChargedJetsMRT.Fill(LeadingChargedJetMRT);
         HLeadingChargedJetsR.Fill(LeadingChargedJetR);
         HLeadingChargedJetsMRVsR.Fill(LeadingChargedJetMR, LeadingChargedJetR);
      }

      // MR, R from truth b-jets
      if(BFromLQIndex >= 0 && BFromLQbarIndex >= 0)
      {
         double BFromLQMR = GetMR(Tree[BFromLQIndex].P, Tree[BFromLQbarIndex].P);
         double BFromLQMRT = GetMRT(Tree[BFromLQIndex].P, Tree[BFromLQbarIndex].P, VisibleFinalME);
         double BFromLQR = GetR(Tree[BFromLQIndex].P, Tree[BFromLQbarIndex].P, VisibleFinalME);

         HBFromLQMR.Fill(BFromLQMR);
         HBFromLQMRT.Fill(BFromLQMRT);
         HBFromLQR.Fill(BFromLQR);
         HBFromLQMRVsR.Fill(BFromLQMR, BFromLQR);
      }
   }

   PsFile.AddTextPage("LQ Distributions");
   PsFile.AddPlot(HLQPT, "", true);
   PsFile.AddPlot(HLQP, "", true);
   PsFile.AddPlot(HLQMass, "", false);
   PsFile.AddPlot(HLQEta, "", true);
   PsFile.AddPlot(HLQRapidity, "", true);
   PsFile.AddPlot(HLQMother, "", true);
   PsFile.AddPlot(HLQBeta, "", false);
   PsFile.AddPlot(HLQGamma, "", true);
   PsFile.AddPlot(HLQTravelLength, "", true);

   PsFile.AddTextPage("LQPair Distributions");
   PsFile.AddPlot(HLQPairPT, "", true);
   PsFile.AddPlot(HLQPairP, "", true);
   PsFile.AddPlot(HLQPairMass, "", true);
   PsFile.AddPlot(HLQPairEta, "", true);
   PsFile.AddPlot(HLQPairRapidity, "", true);
   PsFile.AddPlot(HLQPairFromQQbarRapidity, "", true);
   PsFile.AddPlot(HLQPairAngle, "", false);
   PsFile.AddPlot(HLQPairBeta, "", false);
   PsFile.AddPlot(HLQPairGamma, "", true);

   PsFile.AddTextPage("Neutrino from LQ Distributions");
   PsFile.AddPlot(HNuFromLQPT, "", true);
   PsFile.AddPlot(HNuFromLQP, "", true);
   PsFile.AddPlot(HNuFromLQMass, "", true);
   PsFile.AddPlot(HNuFromLQEta, "", true);
   PsFile.AddPlot(HNuFromLQRapidity, "", true);

   PsFile.AddTextPage("Neutrino pair from LQ distributions");
   PsFile.AddPlot(HNuPairFromLQPT, "", true);
   PsFile.AddPlot(HNuPairFromLQP, "", true);
   PsFile.AddPlot(HNuPairFromLQMass, "", true);
   PsFile.AddPlot(HNuPairFromLQEta, "", true);
   PsFile.AddPlot(HNuPairFromLQRapidity, "", true);
   PsFile.AddPlot(HNuPairFromLQAngle, "", false);

   PsFile.AddTextPage("Event-wise neutrino distributions");
   PsFile.AddPlot(HStableNuCount, "hist text0", true);
   PsFile.AddPlot(HStableNubarCount, "hist text0", true);
   PsFile.AddPlot(HNuCount, "hist text0", true);
   PsFile.AddPlot(HNubarCount, "hist text0", true);
   PsFile.AddPlot(HStableNuVsStableNubarCount, "colz text0", false);

   PsFile.AddTextPage("b from LQ Distributions");
   PsFile.AddPlot(HBFromLQPT, "", true);
   PsFile.AddPlot(HBFromLQP, "", true);
   PsFile.AddPlot(HBFromLQMass, "", false);
   PsFile.AddPlot(HBFromLQEta, "", true);
   PsFile.AddPlot(HBFromLQRapidity, "", true);

   PsFile.AddTextPage("b quark pair from LQ distributions");
   PsFile.AddPlot(HBPairFromLQPT, "", true);
   PsFile.AddPlot(HBPairFromLQP, "", true);
   PsFile.AddPlot(HBPairFromLQMass, "", true);
   PsFile.AddPlot(HBPairFromLQEta, "", true);
   PsFile.AddPlot(HBPairFromLQRapidity, "", true);
   PsFile.AddPlot(HBPairFromLQAngle, "", false);
   PsFile.AddPlot(HBPTVsBPTFromLQ, "colz");

   PsFile.AddTextPage("Gen-jets, input: |eta| < 2.4, all final visble particles");
   PsFile.AddPlot(HNJet15, "hist text0", true);
   PsFile.AddPlot(HNJet30, "hist text0", true);
   PsFile.AddPlot(HNJet50, "hist text0", true);
   PsFile.AddPlot(HNJet100, "hist text0", true);
   PsFile.AddPlot(HNJet150, "hist text0", true);
   PsFile.AddPlot(HLeadingJetPT, "", true);
   PsFile.AddPlot(HLeadingJetEta, "", true);
   PsFile.AddPlot(HLeadingJetMultiplicity, "", true);
   
   PsFile.AddTextPage("Gen-jets, input: |eta| < 2.4, all final visble charged particles");
   PsFile.AddPlot(HNChargedJet15, "hist text0", true);
   PsFile.AddPlot(HNChargedJet30, "hist text0", true);
   PsFile.AddPlot(HNChargedJet50, "hist text0", true);
   PsFile.AddPlot(HNChargedJet100, "hist text0", true);
   PsFile.AddPlot(HNChargedJet150, "hist text0", true);
   PsFile.AddPlot(HLeadingChargedJetPT, "", true);
   PsFile.AddPlot(HLeadingChargedJetEta, "", true);
   PsFile.AddPlot(HLeadingChargedJetMultiplicity, "", true);

   PsFile.AddTextPage("Closest gen-jet to b from LQ");
   PsFile.AddPlot(HBFromLQClosestJetAngle, "", true);
   PsFile.AddPlot(HBFromLQClosestJetDR, "", true);
   PsFile.AddPlot(HBFromLQClosestJetDPhi, "", true);
   PsFile.AddPlot(HBFromLQClosestJetPTRatio, "", true);
   PsFile.AddPlot(HBFromLQClosestJetMultiplicity, "text0 hist", true);
   
   PsFile.AddTextPage("Closest charged jet to b from LQ");
   PsFile.AddPlot(HBFromLQClosestChargedJetAngle, "", true);
   PsFile.AddPlot(HBFromLQClosestChargedJetDR, "", true);
   PsFile.AddPlot(HBFromLQClosestChargedJetDPhi, "", true);
   PsFile.AddPlot(HBFromLQClosestChargedJetPTRatio, "", true);
   PsFile.AddPlot(HBFromLQClosestChargedJetMultiplicity, "text0 hist", true);
   
   PsFile.AddTextPage("MR and R distributions from all final visible particles");
   PsFile.AddPlot(HVisibleMR, "", false);
   PsFile.AddPlot(HVisibleMRT, "", false);
   PsFile.AddPlot(HVisibleR, "", false);
   PsFile.AddPlot(HVisibleMRVsR, "colz", false);

   PsFile.AddTextPage("MR and R distributions from leading two jets");
   PsFile.AddPlot(HLeadingJetsMR, "", false);
   PsFile.AddPlot(HLeadingJetsMRT, "", false);
   PsFile.AddPlot(HLeadingJetsR, "", false);
   PsFile.AddPlot(HLeadingJetsMRVsR, "colz", false);
   
   PsFile.AddTextPage("MR and R distributions, leading jets (smeared 20%)");
   PsFile.AddPlot(HLeadingJetsSmearedMR, "", false);
   PsFile.AddPlot(HLeadingJetsSmearedMRT, "", false);
   PsFile.AddPlot(HLeadingJetsSmearedR, "", false);
   PsFile.AddPlot(HLeadingJetsSmearedMRVsR, "colz", false);
   
   PsFile.AddTextPage("MR and R distributions from leading two charged jets");
   PsFile.AddPlot(HLeadingChargedJetsMR, "", false);
   PsFile.AddPlot(HLeadingChargedJetsMRT, "", false);
   PsFile.AddPlot(HLeadingChargedJetsR, "", false);
   PsFile.AddPlot(HLeadingChargedJetsMRVsR, "colz", false);
   
   PsFile.AddTextPage("MR and R distributions from b quarks from LQ");
   PsFile.AddPlot(HBFromLQMR, "", false);
   PsFile.AddPlot(HBFromLQMRT, "", false);
   PsFile.AddPlot(HBFromLQR, "", false);
   PsFile.AddPlot(HBFromLQMRVsR, "colz", false);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();
}

map<int, int> ReadParticleCharge(string FileName)
{
   map<int, int> ParticleCharge;

   ifstream in(FileName.c_str());

   while(in)
   {
      int temp1 = 0;
      int temp2 = 999999;

      in >> temp1 >> temp2;

      if(temp2 != 999999)
         ParticleCharge.insert(pair<int, int>(temp1, temp2));
   }

   return ParticleCharge;
}

int FindFirstIndex(GenParticleTree &Tree, int PDGID, int Status)
{
   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Status > 0 && Tree[i].StatusCode != Status)
         continue;
      if(Tree[i].PDGID == PDGID)
         return i;
   }

   return -1;
}

double FindPhiPartitionForRazor(vector<GenParticle> &Particles)
{
   double BestPartition = 0;
   double BestSumMass2 = 9999999999.99999999;

   sort(Particles.begin(), Particles.end(), GenParticle::SortByPhi());

   vector<double> ParticlePhi;
   for(int i = 0; i < (int)Particles.size(); i++)
      ParticlePhi.push_back(GetPhi(Particles[i].P));

   int StartIndex = 0;
   for(int i = 0; ParticlePhi[i] < PI && i < (int)Particles.size(); i++)
   {
      double PhiPartition = ParticlePhi[i];

      double P1[4] = {0, 0, 0, 0};
      double P2[4] = {0, 0, 0, 0};

      for(int j = 0; j < (int)Particles.size(); j++)
      {
         if(PhiPartition <= ParticlePhi[j] && ParticlePhi[j] < PhiPartition + PI)
         {
            P1[0] = P1[0] + Particles[j].P[0];
            P1[1] = P1[1] + Particles[j].P[1];
            P1[2] = P1[2] + Particles[j].P[2];
            P1[3] = P1[3] + Particles[j].P[3];
         }
         else
         {
            P2[0] = P2[0] + Particles[j].P[0];
            P2[1] = P2[1] + Particles[j].P[1];
            P2[2] = P2[2] + Particles[j].P[2];
            P2[3] = P2[3] + Particles[j].P[3];
         }
      }

      double SumMass2 = GetMass2(P1) + GetMass2(P2);
      if(SumMass2 < BestSumMass2)
      {
         BestSumMass2 = SumMass2;
         BestPartition = PhiPartition;
      }
   }

   return BestPartition;
}



