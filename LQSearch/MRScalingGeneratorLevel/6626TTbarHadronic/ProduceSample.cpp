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
#include "TFile.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"
#include "TauHelperFunctions2.h"

int main(int argc, char *argv[]);
void GenerateSample();
GenParticleTree GenerateAndFillTree(Pythia &pythia);

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

   GenerateSample();
}

void GenerateSample()
{
   Pythia pythia;
   pythia.readString("Top:all = on");           // turn on top production
   pythia.readString("Top:qq2tq(t:W) = off");   // turn off single-top production
   pythia.readString("Top:ffbar2tqbar(s:W) = off");
   pythia.readString("Random:setSeed = on");    // use random seed
   pythia.readString("Random:seed = 0");        // seed == time, ie., no repetition if rerun
   pythia.readString("Tune:pp = 5");            // pp collision tune 4C
   pythia.init(2212, 2212, 7000);

   TFile Output("TTbar_MRTree.root", "RECREATE");

   double MR = 0;
   double R = 0;

   TTree OutputTree("MRTree", "MRTree");
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");

   for(int i = 0; i < 100000; i++)
   {
      if((i + 1) % 100000 == 0)
         cout << "Producing sample " << i + 1 << endl;

      GenParticleTree Tree = GenerateAndFillTree(pythia);

      bool HasHighPTLepton = false;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         double PT = FourVector(Tree[j].P).GetPT();
         if((Tree[j].PDGID == 13 || Tree[j].PDGID == -13) && Tree[j].StatusCode == 1 && PT > 20)
            HasHighPTLepton = true;
      }
      if(HasHighPTLepton == false)
      {
         i = i - 1;
         continue;
      }

      vector<PseudoJet> VisibleParticles;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].PDGID == 12 || Tree[j].PDGID == -12)
            continue;
         if(Tree[j].PDGID == 14 || Tree[j].PDGID == -14)
            continue;
         if(Tree[j].PDGID == 16 || Tree[j].PDGID == -16)
            continue;
         if(Tree[j].StatusCode != 1)
            continue;
         if(fabs(FourVector(Tree[j].P).GetEta()) > 2.4)
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[j].P[1], Tree[j].P[2], Tree[j].P[3], Tree[j].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(1);

      FourVector MissingEnergy;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;
         
         if(Tree[j].PDGID == 12 || Tree[j].PDGID == -12)
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
         else if(Tree[j].PDGID == 14 || Tree[j].PDGID == -14)
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
         else if(Tree[j].PDGID == 16 || Tree[j].PDGID == -16)
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
         else if(fabs(FourVector(Tree[j].P).GetEta()) > 2.4)
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
      }

      vector<FourVector> GoodJets;
      for(int j = 0; j < (int)Jets.size(); j++)
         if(Jets[j].perp() > 30 && fabs(Jets[j].eta()) < 2.4)
            GoodJets.push_back(FourVector(Jets[j].e(), Jets[j].px(), Jets[j].py(), Jets[j].pz()));

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets);

      MR = GetMR(Hemispheres[0], Hemispheres[1]);
      R = GetR(Hemispheres[0], Hemispheres[1], MissingEnergy);

      if(MR != MR)
         continue;
      if(R != R)
         continue;

      OutputTree.Fill();
   }

   OutputTree.Write();
   Output.Close();
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




