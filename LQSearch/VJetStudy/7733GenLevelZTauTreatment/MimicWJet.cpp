#include <iostream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "TauHelperFunctions2.h"
#include "DrawRandom.h"

int main();
double DrawFraction();

int main()
{
   TChain InputTree("DelphesPlainTree", "DelphesPlainTree");
   for(int i = 1; i <= 10; i++)
      InputTree.AddFile(Form("ZSample/run_%02d.root", i));

   int ParticleCount = 0;
   InputTree.SetBranchAddress("ParticleCount", &ParticleCount);

   double ParticleE[1000] = {0};
   double ParticleX[1000] = {0};
   double ParticleY[1000] = {0};
   double ParticleZ[1000] = {0};
   int ParticleStatus[1000] = {0};
   int ParticlePDGID[1000] = {0};
   int ParticleM1[1000] = {0};

   InputTree.SetBranchAddress("E", ParticleE);
   InputTree.SetBranchAddress("Px", ParticleX);
   InputTree.SetBranchAddress("Py", ParticleY);
   InputTree.SetBranchAddress("Pz", ParticleZ);
   InputTree.SetBranchAddress("Status", ParticleStatus);
   InputTree.SetBranchAddress("PDGID", ParticlePDGID);
   InputTree.SetBranchAddress("M1", ParticleM1);

   TFile OutputFile("Output.root", "recreate");

   TTree OutputTree("ZTree", "Z Tree");

   double MR, R, MRNew, RNew, Fraction;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MRNew", &MRNew, "MRNew/D");
   OutputTree.Branch("RNew", &RNew, "RNew/D");
   OutputTree.Branch("Fraction", &Fraction, "Fraction/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      if(ParticleCount == 0)   // rejected event
         continue;

      FourVector ME(0, 0, 0, 0);
      vector<PseudoJet> Particles;
      for(int i = 0; i < ParticleCount; i++)
      {
         if(ParticleStatus[i] != 1)
            continue;

         FourVector ParticleP(ParticleE[i], ParticleX[i], ParticleY[i], ParticleZ[i]);

         if(ParticlePDGID[i] == 12 || ParticlePDGID[i] == -12
            || ParticlePDGID[i] == 14 || ParticlePDGID[i] == -14
            || ParticlePDGID[i] == 16 || ParticlePDGID[i] == -16
            || ParticlePDGID[i] == 13 || ParticlePDGID[i] == -13)   // sample is mu mu - imitate nu nu
         {
            ME = ME + ParticleP;
            continue;
         }

         if(ParticleP.GetAbsEta() > 3)
         {
            ME = ME + ParticleP;
            continue;
         }

         Particles.push_back(PseudoJet(ParticleX[i], ParticleY[i], ParticleZ[i], ParticleE[i]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> PseudoJets = Sequence.inclusive_jets(0.5);

      vector<FourVector> Jets;
      for(int i = 0; i < (int)PseudoJets.size(); i++)
      {
         if(PseudoJets[i].perp() < 40)
            continue;

         Jets.push_back(FourVector(PseudoJets[i].e(), PseudoJets[i].px(), PseudoJets[i].py(), PseudoJets[i].pz()));
      }

      FourVector MENew(0, 0, 0, 0);
      vector<PseudoJet> ParticlesNew;
      for(int i = 0; i < ParticleCount; i++)
      {
         if(ParticleStatus[i] != 1)
            continue;

         FourVector ParticleP(ParticleE[i], ParticleX[i], ParticleY[i], ParticleZ[i]);

         if(ParticlePDGID[i] == 12 || ParticlePDGID[i] == -12
            || ParticlePDGID[i] == 14 || ParticlePDGID[i] == -14
            || ParticlePDGID[i] == 16 || ParticlePDGID[i] == -16
            || ParticlePDGID[i] == 13)   // sample is mu mu - imitate nu nu
         {
            MENew = MENew + ParticleP;
            continue;
         }

         if(ParticleP.GetAbsEta() > 3)
         {
            MENew = MENew + ParticleP;
            continue;
         }

         if(ParticlePDGID[i] == -13)
         {
            Fraction = DrawFraction();

            MENew = MENew + ParticleP * Fraction;
            ParticlesNew.push_back(PseudoJet(ParticleX[i] * (1 - Fraction),
               ParticleY[i] * (1 - Fraction), ParticleZ[i] * (1 - Fraction), ParticleE[i] * (1 - Fraction)));
         }
         else
            ParticlesNew.push_back(PseudoJet(ParticleX[i], ParticleY[i], ParticleZ[i], ParticleE[i]));
      }
      JetDefinition DefinitionNew(antikt_algorithm, 0.5);
      ClusterSequence SequenceNew(ParticlesNew, DefinitionNew);
      vector<PseudoJet> PseudoJetsNew = SequenceNew.inclusive_jets(0.5);

      vector<FourVector> JetsNew;
      for(int i = 0; i < (int)PseudoJetsNew.size(); i++)
      {
         if(PseudoJetsNew[i].perp() < 40)
            continue;

         JetsNew.push_back(FourVector(PseudoJetsNew[i].e(), PseudoJetsNew[i].px(),
            PseudoJetsNew[i].py(), PseudoJetsNew[i].pz()));
      }

      MR = 0;
      R = 0;
      MRNew = 0;
      RNew = 0;

      if(Jets.size() >= 2)
      {
         vector<FourVector> Group = SplitIntoGroups(Jets, true);

         MR = Get2011MR(Group[0], Group[1]);
         R = Get2011R(Group[0], Group[1], ME);
      }
      if(JetsNew.size() >= 2)
      {
         vector<FourVector> Group = SplitIntoGroups(JetsNew, true);

         MRNew = Get2011MR(Group[0], Group[1]);
         RNew = Get2011R(Group[0], Group[1], MENew);
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();


   return 0;
}

double DrawFraction()
{
   double Value = 0;

   bool Found = false;
   while(Found == false)
   {
      Value = DrawRandom(0, 1);
      
      if(Value < 0.55)
         Found = true;
      else
      {
         double Check = DrawRandom(0, 1);
         if(Check < (1 - Value) / (1 - 0.55))
            Found = true;
      }
   }

   return Value;
}

