#include <fstream>
#include <vector>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "GenparticleTree.h"

int main()
{
   Pythia pythia;

   pythia.readString("HardQCD:all = on");
   pythia.readString("PhaseSpace:pTHatMin = 20");

   pythia.readString("Random:setSeed = on");
   pythia.readString("Random:seed = 0");
   
   pythia.init(2212, 2212, 7000);

   ofstream out("QCDPTHatMin20Sample");

   out << 100000 << endl;

   for(int i = 0; i < 100000; i++)
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

      GenParticleTree Event(particles, 0, i + 1);
      Event.SaveToStream(out);
   }

   out.close();
}



