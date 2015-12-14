#include <fstream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "ProgressBar.h"
#include "GenparticleTree2.h"

int main()
{
   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("WeakDoubleBoson:ffbar2gmZgmZ = on"); // turn-on ZZ production

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 8000);                          // Proton-proton collision at 8 TeV

   int NumberOfEntries = 1000000;

   ProgressBar Bar(cout, NumberOfEntries);
   Bar.SetStyle(1);

   ofstream out("ZZFile");

   for(int i = 0; i < NumberOfEntries; i++)
   {
      pythia.next();

      if(i == 0)
         pythia.event.list();

      if(i % 1000 == 0)
      {
         Bar.Update(i);
         Bar.Print();
      }

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

      // Analyze - find out the two Z's
      GenParticleTree Event(Particles, 1, i + 1);

      vector<FourVector> ZVector;
      for(int j = 0; j < Event.ParticleCount(); j++)
      {
         if(Particles[j].PDGID != 23)
            continue;
         if(Particles[j].Daughters.size() == 0)   // WTF
            continue;

         bool HasZAsDaughter = false;
         for(int k = 0; k < (int)Particles[j].Daughters.size(); k++)
            if(Particles[Particles[j].Daughters[k]].PDGID == 23)
               HasZAsDaughter = true;

         if(HasZAsDaughter == false)
            ZVector.push_back(Particles[j].P);
      }

      if(ZVector.size() != 2)   // should be very rare that this happens
         continue;

      out << (ZVector[0] + ZVector[1]).GetMass() << " " << (ZVector[0] + ZVector[1]).GetEta()
         << " " << (ZVector[0] + ZVector[1]).GetPT() << endl;
   }

   Bar.Update(NumberOfEntries);
   Bar.Print();
   Bar.PrintLine();

   out.close();

   return 0;
}



