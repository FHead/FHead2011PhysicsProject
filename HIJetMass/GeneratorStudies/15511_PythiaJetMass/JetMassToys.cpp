#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

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
#include "TEllipse.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TProfile.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree2.h"
#include "SetStyle.h"

#include "CATree.h"

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   int EntryCount = 10;
   cin >> EntryCount;

   TFile File("Output.root", "RECREATE");

   TH1D HJetPT("HJetPT", "Jet PT", 100, 100, 300);
   TH1D HJetEta("HJetEta", "Jet Eta", 100, -1.3, 1.3);
   TH2D HJetMassPT("HJetMassPT", "Jet Mass vs PT;PT;Mass", 100, 100, 300, 100, 0, 50);
   TProfile PJetMassPT("PJetMassPT", "Jet Mass vs PT;PT;Mass", 100, 100, 300);
   TH2D HJetGroomedMassPT("HJetGroomedMassPT", "Jet Groomed Mass vs PT;PT;Mass", 100, 100, 300, 100, 0, 50);
   TProfile PJetGroomedMassPT("PJetGroomedMassPT", "Jet Groomed Mass vs PT;PT;Mass", 100, 100, 300);

   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 5000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      int EventSize = 0;
      cin >> EventSize;
      if(EventSize == 0)
         break;
      
      // Particles
      vector<GenParticle> Particles(EventSize);

      // Loop over particles
      for(int j = 0; j < EventSize; j++)
      {
         cin >> Particles[j].P[0];
         cin >> Particles[j].P[1];
         cin >> Particles[j].P[2];
         cin >> Particles[j].P[3];

         Particles[j].V[0] = 0;
         Particles[j].V[1] = 0;
         Particles[j].V[2] = 0;
         Particles[j].V[3] = 0;

         cin >> Particles[j].PDGID;
         cin >> Particles[j].StatusCode;
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // Fill pseudojets to be passed into fastjet
      vector<PseudoJet> VisibleParticles;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;
         if(Tree[j].PDGID == 12 || Tree[j].PDGID == -12)
            continue;
         if(Tree[j].PDGID == 14 || Tree[j].PDGID == -14)
            continue;
         if(Tree[j].PDGID == 16 || Tree[j].PDGID == -16)
            continue;
         if(Tree[j].P.GetAbsEta() > 3)
            continue;
         if(Tree[j].P.GetPT() < 0.1)
            continue;
         
         VisibleParticles.push_back(PseudoJet(Tree[j].P[1], Tree[j].P[2], Tree[j].P[3], Tree[j].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.4);   // anti-kt, R = 0.4

      // Take the leading jet and get its constituents
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

      FourVector JetP = Nodes[0]->P;
      FourVector GroomedP = Current->P;

      if(JetP.GetAbsEta() < 1.3 && JetP.GetPT() > 100 && JetP.GetPT() < 300)
      {
         HJetPT.Fill(JetP.GetPT());
         HJetEta.Fill(JetP.GetEta());
         HJetMassPT.Fill(JetP.GetPT(), JetP.GetMass());
         PJetMassPT.Fill(JetP.GetPT(), JetP.GetMass());
         HJetGroomedMassPT.Fill(JetP.GetPT(), GroomedP.GetMass());
         PJetGroomedMassPT.Fill(JetP.GetPT(), GroomedP.GetMass());
      }

      delete Nodes[0];
   }

   HJetPT.Write();
   HJetEta.Write();
   HJetMassPT.Write();
   PJetMassPT.Write();
   HJetGroomedMassPT.Write();
   PJetGroomedMassPT.Write();

   File.Close();

   return 0;
}

void NormalizeHistogram(TH1D &H)
{
   double N = H.GetNbinsX();
   double L = H.GetXaxis()->GetBinLowEdge(1);
   double R = H.GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;

   H.Scale(1 / H.Integral() / BinSize);
}


