#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Pythia8/Pythia.h"
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

#include "Code/TauHelperFunctions3.h"
#include "PlotHelper4.h"
#include "GenparticleTree.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.readString("Beams:eCM = 2760.");                 // collisions at 2.76 TeV
   pythia.readString("Beams:idA = 2212");                  // proton
   pythia.readString("Beams:idB = 2212");                  // proton
   pythia.readString("PhaseSpace:pTHatMin = 50.");

   pythia.readString("HardQCD:all = on");
   // pythia.readString("PromptPhoton:all = on");

   // pythia.readString("Tune:pp = 15");                      // CMS CUETP8S1-CTEQ6L1 tune

   pythia.init();

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
         Particles[j].StatusCode = pythia.event[j].statusHepMC();

         Particles[j].Mothers = pythia.event[j].motherList();
         Particles[j].Daughters = pythia.event[j].daughterList();
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);
   }

   return 0;
}

