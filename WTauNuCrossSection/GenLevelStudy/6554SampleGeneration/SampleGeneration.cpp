#include <fstream>
#include <vector>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "GenparticleTree.h"

int main()
{
   Pythia pythia;

   pythia.readString("WeakSingleBoson:all = on");       // turn on vector bosons: we want some tau particles
   // pythia.readString("WeakDoubleBoson:all = off");
   // pythia.readString("WeakBosonAndParton:all = off");

   pythia.readString("WeakSingleBoson:ffbar2gmZ = off");   // turn off Z
   pythia.readString("WeakSingleBoson:ffbar2ffbar(s:gm) = off");

   pythia.readString("24:oneChannel = 1 1 0 -15 16");   // force W to decay to tau nu
   pythia.readString("23:oneChannel = 1 1 0 16 -16");   // force Z to decay to tau tau

   pythia.readString("Random:setSeed = on");
   pythia.readString("Random:seed = 0");
   
   pythia.init(2212, 2212, 7000);

   ofstream out("TauEnrichedWSample");

   out << 1000 << endl;

   for(int i = 0; i < 1000; i++)
   {
      bool ExistW = false;
      while(ExistW == false)
      {
         pythia.next();

         for(int j = 0; j < pythia.event.size(); j++)
         {
            if(pythia.event[j].id() == 24 || pythia.event[j].id() == -24)
            {
               ExistW = true;
               break;
            }
         }
      }

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



