#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName);
int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID);
int TraceBHadron(GenParticleTree &Tree, int StartIndex);
int FollowToTheEnd(GenParticleTree &Tree, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi);
double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy23_ISRScaled.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 23");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   DoToyAndAppendPlots(PsFile, 150, "LQ150.root");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("OutputTree", "Tree! ®");

   stringstream LQMassStream;
   LQMassStream << "42: m0 = " << LQMass;

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("42:0:products = 5 16");              // Force decay to b nu_tau
   pythia.readString(LQMassStream.str().c_str());          // LQ mass set to input value
   pythia.readString("LeptoQuark:gg2LQLQbar = on");        // production mechanism: gg
   pythia.readString("LeptoQuark:qqbar2LQLQbar = on");     // production mechanism: qqbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("PartonLevel:all = on");              // Master switch for parton step
   pythia.readString("PartonLevel:ISR = on");              // Turn on ISR
   pythia.readString("PartonLevel:FSR = on");              // Turn on FSR
   pythia.readString("PartonLevel:MI = off");              // No multiple interaction (for now)
   
   pythia.readString("HadronLevel:all = off");             // No hadronization yet for this study

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   int EntryCount = 10000;
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      // Generate event
      pythia.next();

      // Particles
      vector<GenParticle> Particles(pythia.event.size());

      // Loop over particles
      for(int j = 0; j < pythia.event.size(); j++)
      {
         Particles[j].P[0] = pythia.event[j].e();
         Particles[j].P[1] = pythia.event[j].px();
         Particles[j].P[2] = pythia.event[j].py();
         Particles[j].P[3] = pythia.event[j].pz();
         
         Particles[j].V[0] = pythia.event[j].tProd();
         Particles[j].V[1] = pythia.event[j].xProd();
         Particles[j].V[2] = pythia.event[j].yProd();
         Particles[j].V[3] = pythia.event[j].zProd();

         Particles[j].PDGID = pythia.event[j].id();
         Particles[j].StatusCode = pythia.event.statusHepMC(j);

         Particles[j].Mothers = pythia.event.motherList(j);
         Particles[j].Daughters = pythia.event.daughterList(j);
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // find b's and nu's
      int OriginalB1Index = FindChildIndex(Tree, 5, 42);
      int OriginalB2Index = FindChildIndex(Tree, -5, -42);
      int OriginalNu1Index = FindChildIndex(Tree, 16, 42);
      int OriginalNu2Index = FindChildIndex(Tree, -16, -42);

      int B1Index = TraceBHadron(Tree, OriginalB1Index);
      int B2Index = TraceBHadron(Tree, OriginalB2Index);
      int Nu1Index = FollowToTheEnd(Tree, OriginalNu1Index);
      int Nu2Index = FollowToTheEnd(Tree, OriginalNu2Index);

      FourVector B1P = FourVector(Tree[B1Index].P);
      FourVector B2P = FourVector(Tree[B2Index].P);
      FourVector Nu1P = FourVector(Tree[Nu1Index].P);
      FourVector Nu2P = FourVector(Tree[Nu2Index].P);

      // get all stable particles - excluding spectators (and final nu nu b b)
      vector<int> StableIndices = ListStableParticle(Tree);
      vector<FourVector> StableP;
      for(int i = 0; i < (int)StableIndices.size(); i++)
      {
         if(StableIndices[i] == B1Index || StableIndices[i] == B2Index
            || StableIndices[i] == Nu1Index || StableIndices[i] == Nu2Index)
         {
            StableIndices.erase(StableIndices.begin() + i);
            i = i - 1;
            continue;
         }

         bool HasProtonMom = false;
         for(int j = 0; j < (int)Tree[StableIndices[i]].Mothers.size(); j++)
         {
            if(Tree[Tree[StableIndices[i]].Mothers[j]].PDGID == 2212)
            {
               HasProtonMom = true;
               break;
            }
         }

         if(HasProtonMom == false)
            StableP.push_back(FourVector(Tree[StableIndices[i]].P));
         else
         {
            StableIndices.erase(StableIndices.begin() + i);
            i = i - 1;
         }
      }

      // Get BetaZ
      FourVector EventTotalP(0, 0, 0, 0);
      for(int i = 0; i < (int)StableP.size(); i++)
         EventTotalP = EventTotalP + StableP[i];

      double BetaZ = EventTotalP[3] / EventTotalP[0];

      // Boost the BetaZ away for ALL OF THEM
      for(int i = 0; i < (int)StableP.size(); i++)
         StableP[i] = StableP[i].BoostZ(BetaZ);
      B1P = B1P.BoostZ(BetaZ);
      B2P = B2P.BoostZ(BetaZ);
      Nu1P = Nu1P.BoostZ(BetaZ);
      Nu2P = Nu2P.BoostZ(BetaZ);

      // Get BetaX
      FourVector HardProcessTotalP = B1P + B2P + Nu1P + Nu2P;
      double BetaX = HardProcessTotalP.GetPT() / HardProcessTotalP[0];

      FourVector TransverseDirection = HardProcessTotalP;
      TransverseDirection[0] = 0;
      TransverseDirection[3] = 0;

      // Boost BetaX away
      B1P = B1P.Boost(TransverseDirection, BetaX);
      B2P = B2P.Boost(TransverseDirection, BetaX);
      Nu1P = Nu1P.Boost(TransverseDirection, BetaX);
      Nu2P = Nu2P.Boost(TransverseDirection, BetaX);

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();
}

int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID)
{
   int MotherIndex = -1;

   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].PDGID == ChildPDGID)
      {
         for(int j = 0; j < (int)Tree[i].Mothers.size(); j++)
         {
            if(Tree[Tree[i].Mothers[j]].PDGID == ParentPDGID)
               return i;
         }
      }
   }

   return -1;
}

int TraceBHadron(GenParticleTree &Tree, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= Tree.ParticleCount())
      return -1;
   if(HasB(Tree[StartIndex].PDGID) == false && Tree[StartIndex].PDGID != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;;
      for(int i = 0; i < (int)Tree[CurrentIndex].Daughters.size(); i++)
      {
         if(Tree[Tree[CurrentIndex].Daughters[i]].PDGID != 92
            && HasB(Tree[Tree[CurrentIndex].Daughters[i]].PDGID) == false)
            continue;
         ChildrenIndex.push_back(Tree[CurrentIndex].Daughters[i]);
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      //    otherwise return this candidate
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = FourVector(Tree[ChildrenIndex[0]].P).GetPT();
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = FourVector(Tree[ChildrenIndex[i]].P).GetPT();
            if(PT > BestCandidatePT)
            {
               BestCandidate = i;
               BestCandidatePT = PT;
            }
         }

         CurrentIndex = ChildrenIndex[BestCandidate];
      }
   }

   return -1;

}

int FollowToTheEnd(GenParticleTree &Tree, int StartIndex)
{
   // This function is used to trace neutrinos.
   // They should only have one child, so tracing through the first child is ok.
   // This function should NOT be used for anything other than neutrinos!!!!

   while(Tree[StartIndex].Daughters.size() > 0)
      StartIndex = Tree[StartIndex].Daughters[0];

   return StartIndex;
}

bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)
   //    s is spin, let's happily ignore

   if(PDGID < 0)
      PDGID = -PDGID;

   if(PDGID == 5)
      return true;
   if((PDGID % 100) / 10 == 5)
      return true;
   if((PDGID % 1000) / 100 == 5)
      return true;
   if((PDGID % 10000) / 1000 == 5)
      return true;

   return false;
}

int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < (int)Jets.size(); i++)
   {
      double EtaJet = Jets[i].eta();
      double PhiJet = Jets[i].phi();

      double DEta = Eta - EtaJet;
      double DPhi = Phi - PhiJet;
      if(DPhi > PI)   DPhi = DPhi - 2 * PI;
      if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
      double DR = sqrt(DPhi * DPhi + DEta * DEta);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}

double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency)
{
   if(JetPT.size() == 0)
      return 0;
   if(PT < JetPT[0])
      return 0;
   if(PT > JetPT[JetPT.size()-1])
      return JetEfficiency[JetPT.size()-1];

   for(int i = 0; i < JetPT.size() - 1; i++)
   {
      if(JetPT[i] < PT && JetPT[i+1] >= PT)
         return JetEfficiency[i] +
            (PT - JetPT[i]) / (JetPT[i+1] - JetPT[i]) * (JetEfficiency[i+1] - JetEfficiency[i]);
   }

   return 0;
}





