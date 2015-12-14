#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "TauHelperFunctions2.h"

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " input output (a|z)" << endl;
      return -1;
   }

   bool IsPhoton = true;
   if(argv[3][0] == 'z')
      IsPhoton = false;
   if(argv[3][0] == 'a')
      IsPhoton = true;

   TChain InputTree("DelphesPlainTree", "DelphesPlainTree");
   InputTree.AddFile(argv[1]);

   int ParticleCount;
   double E[1000];
   double Px[1000];
   double Py[1000];
   double Pz[1000];
   int PDGID[1000];
   int Status[1000];

   InputTree.SetBranchAddress("ParticleCount", &ParticleCount);
   InputTree.SetBranchAddress("E", &E);
   InputTree.SetBranchAddress("Px", &Px);
   InputTree.SetBranchAddress("Py", &Py);
   InputTree.SetBranchAddress("Pz", &Pz);
   InputTree.SetBranchAddress("PDGID", &PDGID);
   InputTree.SetBranchAddress("Status", &Status);

   TFile OutputFile(argv[2], "RECREATE");

   TTree OutputTree("Tree", "Tree");

   double TreeY, TreePT, TreeMR, TreeR;
   OutputTree.Branch("TreeY", &TreeY, "TreeY/D");
   OutputTree.Branch("TreePT", &TreePT, "TreePT/D");
   OutputTree.Branch("TreeMR", &TreeMR, "TreeMR/D");
   OutputTree.Branch("TreeR", &TreeR, "TreeR/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      FourVector HighestBoson(0, 0, 0, 0);
      int HighestIndex = -1;
      for(int i = 0; i < ParticleCount; i++)
      {
         if(IsPhoton == true && PDGID[i] != 22)
            continue;
         if(IsPhoton == true && Status[i] != 1)
            continue;
         if(IsPhoton == false && PDGID[i] != 23)
            continue;

         FourVector P(E[i], Px[i], Py[i], Pz[i]);
         if(P.GetPT() > HighestBoson.GetPT())
         {
            HighestBoson = P;
            HighestIndex = i;
         }
      }

      // Group into jets - also calculate MET along the way
      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < ParticleCount; i++)
      {
         if(Status[i] != 1)   // final particles only
            continue;
         if(PDGID[i] == 16 || PDGID[i] == -16 || PDGID[i] == 14 || PDGID[i] == -14
               || PDGID[i] == 12 || PDGID[i] == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(E[i], Px[i], Py[i], Pz[i]).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(E[i], Px[i], Py[i], Pz[i]).GetPT() < 1)   // mini particles - forget it
            continue;
         if(i == HighestIndex)   // don't use the prompt gamma
            continue;

         VisibleParticles.push_back(PseudoJet(Px[i], Py[i], Pz[i], E[i]));
         MissingEnergy = MissingEnergy - FourVector(E[i], Px[i], Py[i], Pz[i]);
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
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      double MR = -1, R = -1;
      if(GoodJets.size() >= 2 && Groups.size() >= 2)
      {
         MR = Get2011MR(Groups[0], Groups[1]);
         R = Get2011R(Groups[0], Groups[1], MissingEnergy);
      }

      TreeY = HighestBoson.GetY();
      TreePT = HighestBoson.GetPT();
      TreeMR = MR;
      TreeR = R;

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}




