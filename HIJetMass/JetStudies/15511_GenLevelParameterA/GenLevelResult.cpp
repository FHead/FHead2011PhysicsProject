#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "CATree.h"

int main(int argc, char *argv[]);
double GetDPhi(double phi1, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "There is no gen-level information in data!  Exiting!" << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   GenParticleTreeMessenger MGen(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH2D HPTDepth("HPTDepth", ";Jet PT; Depth", 100, 100, 300, 12, 0, 12);
   TProfile PPTDepth("PPTDepth", ";Jet PT; Depth", 100, 100, 300);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      MHiEvent.GetEntry(iEntry);
      MGen.GetEntry(iEntry);
      
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < (int)MGen.ID->size(); i++)
      {
         if((*MGen.ID)[i] == 12 || (*MGen.ID)[i] == -12)
            continue;
         if((*MGen.ID)[i] == 14 || (*MGen.ID)[i] == -14)
            continue;
         if((*MGen.ID)[i] == 16 || (*MGen.ID)[i] == -16)
            continue;
         if((*MGen.Eta)[i] > 3 || (*MGen.Eta)[i] < -3)
            continue;
         if((*MGen.PT)[i] < 0.1)
            continue;
         if((*MGen.DaughterCount)[i] > 0)
            continue;

         FourVector P;
         P.SetPtEtaPhi((*MGen.PT)[i], (*MGen.Eta)[i], (*MGen.Phi)[i]);

         VisibleParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.4);

      // cout << VisibleParticles.size() << " " << MHiEvent.hiBin << endl;

      // Let's look at the leading jet for now!
      int LeadingIndex = 0;
      for(int i = 1; i < (int)Jets.size(); i++)
         if(Jets[i].perp() > Jets[LeadingIndex].perp())
            LeadingIndex = i;

      vector<PseudoJet> Constituents = Jets[LeadingIndex].constituents();

      // Prepare for CA algorithm
      vector<Node *> Nodes;
      for(int i = 0; i < (int)Constituents.size(); i++)
      {
         FourVector P(Constituents[i].e(), Constituents[i].px(), Constituents[i].py(), Constituents[i].pz());
         Nodes.push_back(new Node(P));
      }

      BuildCATree(Nodes);

      // Run the softdrop algorithm
      double zcut = 0.1;
      double beta = 0;
      double r0 = 0.4;

      bool Done = false;
      Node *Current = Nodes[0];

      int Depth = 0;

      while(Done == false)
      {
         if(Current->N == 1)
            Done = true;
         else if(Current->N == 2)
         {
            cerr << "WTF!  Time to Debug!" << endl;
            Done = true;
         }
         else   // N >= 3 => two sub-jets
         {
            double PT1 = Current->Child1->P.GetPT();
            double PT2 = Current->Child2->P.GetPT();
            double PTRatio = min(PT1, PT2) / (PT1 + PT2);

            double DR = GetDR(Current->Child1->P, Current->Child2->P);

            double Threshold = zcut * pow(DR / r0, beta);

            if(PTRatio > Threshold)
               Done = true;
            else
            {
               if(PT1 > PT2)
                  Current = Current->Child1;
               else
                  Current = Current->Child2;

               Depth = Depth + 1;
            }
         }
      }

      if(Nodes[0]->P.GetAbsEta() < 1.3 && Nodes[0]->P.GetPT() > 100 && Nodes[0]->P.GetPT() < 300)
      {
         HPTDepth.Fill(Nodes[0]->P.GetPT(), Depth);
         PPTDepth.Fill(Nodes[0]->P.GetPT(), Depth);
      }

      delete Nodes[0];
   }

   HPTDepth.Write();
   PPTDepth.Write();

   OutputFile.Close();

   InputFile.Close();
}






