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
#include "TEllipse.h"
#include "TLegend.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   Pythia pythia;

   pythia.readString("Beams:eCM = 8000.");
   pythia.readString("HardQCD:all = on");
   pythia.readString("PhaseSpace:pTHatMin = 120.");
   pythia.readString("PhaseSpace:pTHatMax = 260.");

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init();

   TH1D HPT("HPT", "Jet PT;PT", 100, 0, 500);
   TH1D HPTRatio("HPTRatio", "PT Groomed / Original;PT Ratio", 100, 0.5, 1.0);
   TH1D HNDropped("HNDropped", "Dropped Branches;N_{dropped}", 12, 0, 12);
   TH1D HZG120("HZG120", "Z_{g} (PT = 120-140);Z_{g}", 10, 0, 0.5);
   TH1D HZG140("HZG140", "Z_{g} (PT = 140-160);Z_{g}", 10, 0, 0.5);
   TH1D HZG160("HZG160", "Z_{g} (PT = 160-180);Z_{g}", 10, 0, 0.5);
   TH1D HZG180("HZG180", "Z_{g} (PT = 180-200);Z_{g}", 10, 0, 0.5);
   TH1D HMassRatio120("HMassRatio120", "Mass Groomed / original (PT = 120-140);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio140("HMassRatio140", "Mass Groomed / original (PT = 140-160);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio160("HMassRatio160", "Mass Groomed / original (PT = 160-180);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio180("HMassRatio180", "Mass Groomed / original (PT = 180-200);Mass Ratio", 100, 0, 1);

   HPT.SetStats(0);
   HPTRatio.SetStats(0);
   HNDropped.SetStats(0);
   HZG120.SetStats(0);
   HZG140.SetStats(0);
   HZG160.SetStats(0);
   HZG180.SetStats(0);

   HZG120.Sumw2();
   HZG140.Sumw2();
   HZG160.Sumw2();
   HZG180.Sumw2();

   int EntryCount = 100000;
   cout << "[EVENT] " << EntryCount << endl;
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      TH2D HEtaPhi(Form("HEtaPhi_%d", iEntry), Form("Event %d;#eta;#phi", iEntry), 100, -5, 5, 100, -3.14159, 3.14159);
      HEtaPhi.SetStats(0);
   
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

      // How many stable particles are there?
      int StableParticleCount = 0;
      for(int j = 0; j < Tree.ParticleCount(); j++)
         if(Tree[j].StatusCode == 1)
            StableParticleCount = StableParticleCount + 1;

      // Write all stable particles out
      cout << "[EVENT] " << StableParticleCount << endl;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;

         cout << "[EVENT] " << Tree[j].P[0] << " " << Tree[j].P[1] << " " << Tree[j].P[2] << " " << Tree[j].P[3]
            << " " << Tree[j].PDGID << " " << Tree[j].StatusCode << endl;
      }
   }

   return 0;
}

