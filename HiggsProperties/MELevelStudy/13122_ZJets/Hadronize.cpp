#include <iostream>
#include <map>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "Code/TauHelperFunctions2.h"
#include "GenparticleTree.h"

int main()
{
   // Generator
   Pythia pythia;

   // Stick with default values, so do not bother with a separate file
   // for changes. However, do one change, to show readString in action.
   pythia.readString("PartonLevel:ISR = off");
   pythia.readString("PartonLevel:FSR = off");
   pythia.readString("PartonLevel:MPI = off");
   pythia.readString("HadronLevel:Hadronize = on");

   // Initialize Les Houches Event File run.
   pythia.readString("Beams:frameType = 4");
   pythia.readString("Beams:LHEF = unweighted_events.lhe");
   pythia.init();

   ofstream out("ZJetEvent");

   for(int iEvent = 0; ; iEvent = iEvent + 1)
   {
      // cout << endl << "Begin event # " << iEvent << endl;

      // Generate events, and check whether generation failed.
      if(!pythia.next())
      {
         // If failure because reached end of file then exit event loop.
         if(pythia.info.atEndOfFile())
            break;
      }

      // if(iEvent == 0)
      //    pythia.event.list();

      vector<GenParticle> Particles(pythia.event.size());

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

      // write to file...or not?
      GenParticleTree Event(Particles, 1, iEvent + 1);
      // Event.SaveToStream(out);

      // Find highest PT leptons
      multimap<double, int, greater<double> > Leptons;
      for(int i = 0; i < Event.ParticleCount(); i++)
      {
         if(Event[i].StatusCode != 1)   // final particles only
            continue;
         if(Event[i].PDGID == 11 || Event[i].PDGID == 13 || Event[i].PDGID == -11 || Event[i].PDGID == -13)
            Leptons.insert(pair<double, int>(FourVector(Event[i].P).GetPT(), i));
      }

      if(Leptons.size() < 2)
         continue;

      multimap<double, int>::iterator iter = Leptons.begin();
      int ID1 = iter->second;
      iter++;
      int ID2 = iter->second;
      if(Event[ID1].PDGID < Event[ID2].PDGID)
         swap(ID1, ID2);

      // Cluster into jets
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Event.ParticleCount(); i++)
      {
         if(i == ID1 || i == ID2)   // leptons!
            continue;
         if(Event[i].StatusCode != 1)   // final particles only
            continue;
         if(Event[i].PDGID == 16 || Event[i].PDGID == -16 || Event[i].PDGID == 14 || Event[i].PDGID == -14
            || Event[i].PDGID == 12 || Event[i].PDGID == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(Event[i].P).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(Event[i].P).GetPT() < 1)   // mini particles - forget it
            continue;

         VisibleParticles.push_back(PseudoJet(Event[i].P[1], Event[i].P[2], Event[i].P[3], Event[i].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.5

      // Find best jet
      multimap<double, FourVector, greater<double> > SortedJets;
      for(int i = 0; i < (int)Jets.size(); i++)
         SortedJets.insert(pair<double, FourVector>(Jets[i].perp(), FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz())));
      multimap<double, FourVector>::iterator iter2 = SortedJets.begin();

      FourVector L1(Event[ID1].P);
      FourVector L2(Event[ID2].P);
      FourVector J = iter2->second;

      if(GetDR(L1, J) > 0.2 && GetDR(L2, J) > 0.2 && L1.GetPT() > 10 && L2.GetPT() > 10 && J.GetPT() > 15
         && L1.GetAbsEta() < 2.4 && L2.GetAbsEta() < 2.4)
      {
         cout << L1[1] << " " << L1[2] << " " << L1[3] << " ";
         cout << L2[1] << " " << L2[2] << " " << L2[3] << " ";
         cout <<  J[1] << " " <<  J[2] << " " <<  J[3] << endl;
      }

      // cout << L1.GetPT() << " " << L1.GetEta() << " " << L1.GetPhi() << " ";
      // cout << L2.GetPT() << " " << L2.GetEta() << " " << L2.GetPhi() << " ";
      // cout <<  J.GetPT() << " " <<  J.GetEta() << " " <<  J.GetPhi() << endl;
   }

   out.close();

   return 0;
}



