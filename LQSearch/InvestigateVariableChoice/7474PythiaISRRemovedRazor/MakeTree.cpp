#include <iostream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "GenparticleTree.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
int FindChildIndex(GenParticleTree &T, int ChildPDGID, int ParentPDGID);
int TraceBHadron(GenParticleTree &T, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(vector<FourVector> &Jets, FourVector Target);

int main()
{
   SetStyle();

   TFile OutputFile("Output.root", "recreate");
   TTree OutputTree("MRTree", "MRTree");

   double TreeMR;
   double TreeR2;
   double TreeISRMR;
   double TreeISRR2;

   OutputTree.Branch("MR", &TreeMR, "MR/D");
   OutputTree.Branch("R2", &TreeR2, "R2/D");
   OutputTree.Branch("ISRMR", &TreeISRMR, "ISRMR/D");
   OutputTree.Branch("ISRR2", &TreeISRR2, "ISRR2/D");

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("42:0:products = 5 16");              // Force decay to b nu_tau
   pythia.readString("42: m0 = 500");                      // LQ mass set to input value
   pythia.readString("LeptoQuark:gg2LQLQbar = on");        // production mechanism: gg
   pythia.readString("LeptoQuark:qqbar2LQLQbar = on");     // production mechanism: qqbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      pythia.next();

      vector<GenParticle> Particles(pythia.event.size());

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

      FourVector MissingEnergy(0, 0, 0, 0);
      FourVector AllFinalMomentum(0, 0, 0, 0);
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // final particles only
            continue;

         if(fabs(FourVector(Tree[i].P).GetEta()) < 5)
            AllFinalMomentum = AllFinalMomentum + FourVector(Tree[i].P);

         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16 || Tree[i].PDGID == 14 || Tree[i].PDGID == -14
               || Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(Tree[i].P).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(Tree[i].P).GetPT() < 1)   // mini particles - forget it
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         MissingEnergy = MissingEnergy - FourVector(Tree[i].P);
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.5

      vector<FourVector> GoodJets;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 40)
            continue;
         GoodJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));
      }
      if(GoodJets.size() < 2)
         continue;
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      int BFromLQ1 = FindChildIndex(Tree, 5, 42);
      int BFromLQ2 = FindChildIndex(Tree, -5, -42);
      int FinalBFromLQ1 = TraceBHadron(Tree, BFromLQ1);
      int FinalBFromLQ2 = TraceBHadron(Tree, BFromLQ2);

      if(FourVector(Tree[FinalBFromLQ1].P).GetAbsEta() > 3
         || FourVector(Tree[FinalBFromLQ2].P).GetAbsEta() > 3)
         continue;

      int Jet1 = FindClosestJet(GoodJets, Tree[FinalBFromLQ1].P);
      int Jet2 = FindClosestJet(GoodJets, Tree[FinalBFromLQ2].P);

      if(Jet1 < 0 || Jet2 < 0 || Jet1 >= (int)GoodJets.size() || Jet2 >= (int)GoodJets.size())
         continue;
      /*
      if(fabs(GoodJets[Jet1].GetPT() - FourVector(Tree[FinalBFromLQ1].P).GetPT()) / GoodJets[Jet1].GetPT() > 0.2)
         continue;
      if(fabs(GoodJets[Jet2].GetPT() - FourVector(Tree[FinalBFromLQ2].P).GetPT()) / GoodJets[Jet2].GetPT() > 0.2)
         continue;
      */

      FourVector POther(0, 0, 0, 0);
      for(int i = 0; i < GoodJets.size(); i++)
      {
         if(i == Jet1 || i == Jet2)
            continue;
         POther = POther + GoodJets[i];
      }

      double MR2011 = Get2011MR(Groups[0], Groups[1]);
      double R2011 = Get2011R(Groups[0], Groups[1], MissingEnergy);

      double ISRMR = GetISRRemoved2011MR(GoodJets[Jet1], GoodJets[Jet2], POther);
      double ISRR = GetISRRemoved2011R(GoodJets[Jet1], GoodJets[Jet2], POther);

      TreeMR = MR2011;
      TreeR2 = R2011 * R2011;

      TreeISRMR = ISRMR;
      TreeISRR2 = ISRR * ISRR;

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

int FindChildIndex(GenParticleTree &T, int ChildPDGID, int ParentPDGID)
{
   for(int i = 0; i < T.ParticleCount(); i++)
   {
      if(T[i].PDGID != ChildPDGID || T[i].Mothers.size() == 0)
         continue;

      for(int j = 0; j < (int)T[i].Mothers.size(); j++)
         if(T[T[i].Mothers[j]].PDGID == ParentPDGID)
            return i;
   }

   return -1;
}

int TraceBHadron(GenParticleTree &T, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= T.ParticleCount())
      return -1;
   if(HasB(T[StartIndex].PDGID) == false && T[StartIndex].PDGID != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      int ParticleCount = T.ParticleCount();

      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;
      for(int i = 0; i < T[CurrentIndex].Daughters.size(); i++)
      {
         int ID = T[T[CurrentIndex].Daughters[i]].PDGID;
         if(ID != 92 && HasB(ID) == false)
            continue;
         ChildrenIndex.push_back(T[CurrentIndex].Daughters[i]);
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = FourVector(T[ChildrenIndex[0]].P).GetPT();
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = FourVector(T[ChildrenIndex[i]].P).GetPT();
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

bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)

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

int FindClosestJet(vector<FourVector> &Jets, FourVector Target)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < (int)Jets.size(); i++)
   {
      double DR = GetDR(Jets[i], Target);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}

