#include <fstream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "GenparticleTree.h"

int main()
{
   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Top:gg2ttbar = on");                 // gg -> ttbar
   pythia.readString("Top:qqbar2ttbar(s:gmZ) = on");       // qqbar -> g -> ttbar
   pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");       // ffbar -> gamma*/Z0 -> ttbar
   pythia.readString("Top:gmgm2ttbar = on");               // gamma gamma -> ttbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("PartonLevel:all = on");              // master switch for parton step
   pythia.readString("PartonLevel:ISR = on");              // turning on ISR
   pythia.readString("PartonLevel:FSR = off");             // turning off FSR
   pythia.readString("PartonLevel:MI = off");              // no multiple interaction

   pythia.readString("HadronLevel:all = off");             // hadronize?  don't do anything yet

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   ofstream out("Pythia8_NoFSRMI_NoHadronization_TTbar");

   int NumberOfEntries = 100000;

   SaveHelper Helper;
   Helper.IntValue = NumberOfEntries;
   out.write(Helper.CharValue, 16);

   for(int i = 0; i < NumberOfEntries; i++)
   {
      pythia.next();

      if(i == 0)
         pythia.event.list();

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

      // write to file
      GenParticleTree Event(Particles, 1, i + 1);
      Event.SaveToStream(out);
   }

   out.close();
}



