#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions2.h"

#include "Messenger.h"
#include "BasicUtilities.h"
#include "CATree.h"

int main()
{
   TFile File("HiForestAOD_999.root");

   HiEventTreeMessenger MHiEvent(File);
   JetTreeMessenger MJet(File);
   PFTreeMessenger MPF(File);
   RhoTreeMessenger MRho(File);

   if(MHiEvent.Tree == NULL)
      return -1;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);

      vector<PseudoJet> Particles;
      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
         P[0] = (*MPF.E)[i];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      double GhostArea = 0.0005;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      vector<PseudoJet> NewJets(Jets.size());
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         double rho = GetRho(MRho.EtaMax, MRho.Rho, Jets[i].eta());
         double rhom = GetRho(MRho.EtaMax, MRho.RhoM, Jets[i].eta());
         contrib::ConstituentSubtractor Subtractor(rho, rhom);
         Subtractor.set_alpha(1);  // optional
         // subtractor.set_max_deltaR(2);  // optional
         NewJets[i] = Subtractor(Jets[i]);
      }

      vector<PseudoJet> CSCandidates;
      for(int i = 0; i < (int)NewJets.size(); i++)
      {
         vector<PseudoJet> Candidates = NewJets[i].constituents();
         CSCandidates.insert(CSCandidates.end(), Candidates.begin(), Candidates.end());
      }
      ClusterSequence NewSequence(CSCandidates, Definition);
      vector<PseudoJet> SDJets = NewSequence.inclusive_jets();

      for(int i = 0; i < (int)SDJets.size(); i++)
      {
         if(SDJets[i].perp() < 10)
            continue;

         vector<Node *> Nodes;

         vector<PseudoJet> Candidates = SDJets[i].constituents();
         if(Candidates.size() < 1)
            continue;

         for(int j = 0; j < (int)Candidates.size(); j++)
         {
            FourVector P;
            P[0] = Candidates[j].e();
            P[1] = Candidates[j].px();
            P[2] = Candidates[j].py();
            P[3] = Candidates[j].pz();
            Nodes.push_back(new Node(P));
         }
         
         BuildCATree(Nodes);

         Node *Groomed = FindSDNode(Nodes[0]);

         cout << Groomed->P.GetMass() << " " << Groomed->P.GetPT() << " " << Groomed->P.GetMass() / Groomed->P.GetPT() << endl;

         delete Nodes[0];
      }
      cout << endl;
   }

   File.Close();

   return 0;
}





