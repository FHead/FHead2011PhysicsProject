//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph 5 v. 1.4.2, 2012-02-16
// By the MadGraph Development Team
// Please visit us at https://launchpad.net/madgraph5
// File based on main25.cc in Pythia 8.149
//==========================================================================

#include <vector>
using namespace std;

#include "Pythia.h"
#include "Sigma_sm_gg_zqq.h"
#include "Sigma_sm_gq_zgq.h"
#include "Sigma_sm_qq_zqq.h"
#include "Sigma_sm_qq_zgg.h"
#include "Sigma_sm_gq_zq.h"
#include "Sigma_sm_qq_zg.h"
#include "Sigma_sm_qq_z.h"
using namespace Pythia8; 

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"

#include "GenparticleTree.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

int main() 
{
   // Number of events to generate and to list. Max number of errors.
   // Warning: generation of complete events is much slower than if you use
   // PartonLevel:all = off to only get cross sections, so adjust nEvent.
   int nEvent = 10000; 
   int nList = 1; 
   int nAbort = 5; 

   // Pythia generator.
   Pythia pythia; 

   // Read param_card file
   pythia.readString("SLHA:file = ../Processes_sm/param_card_sm.dat"); 

   // Provide process pointers to Pythia
   pythia.setSigmaPtr(new Sigma_sm_gg_zqq()); 
   pythia.setSigmaPtr(new Sigma_sm_gq_zgq()); 
   pythia.setSigmaPtr(new Sigma_sm_qq_zqq()); 
   pythia.setSigmaPtr(new Sigma_sm_qq_zgg()); 
   pythia.setSigmaPtr(new Sigma_sm_gq_zq()); 
   pythia.setSigmaPtr(new Sigma_sm_qq_zg()); 
   pythia.setSigmaPtr(new Sigma_sm_qq_z()); 

   // Phase space cut on pThat.
   pythia.readString("PhaseSpace:pTHatMin = 20."); 

   // Optionally only compare cross sections.
   // pythia.readString("PartonLevel:all = off"); 

   // Initialization for LHC.
   pythia.init(2212, 2212, 7000.); 

   // List changes.
   pythia.settings.listChanged(); 
   pythia.particleData.listChanged(); 

   // output stream
   ofstream out("ZJetEvents");

   // number of entries
   SaveHelper Helper;
   Helper.IntValue = nEvent;
   out.write(Helper.CharValue, 16);

   // Test histogram
   TH1D HJetCount30("HJetCount30", "Number of jets above 30 GeV", 10, -0.5, 9.5);

   // Begin event loop.
   int iAbort = 0; 
   for (int iEvent = 0; iEvent < nEvent; ++ iEvent)
   {
      if (iEvent%(max(1, nEvent/20)) == 0)
         cout <<  " Now begin event " << iEvent <<  "\n"; 

      // Generate events. Quit if many failures.
      if ( !pythia.next())
      {
         if (++ iAbort < nAbort)
            continue; 
         cout <<  " Event generation aborted prematurely, owing to error!\n"; 
         break; 
      }

      // List first few events.
      if (iEvent < nList)
      {
         pythia.info.list(); 
         pythia.process.list(); 
         pythia.event.list(); 
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

      // write to file
      GenParticleTree Event(Particles, 1, iEvent + 1);
      Event.SaveToStream(out);

      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Event.ParticleCount(); i++)
      {
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
         MissingEnergy = MissingEnergy - FourVector(Event[i].P);
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.5

      int JetCount30 = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
         if(Jets[i].perp() > 30 && Jets[i].eta() < 3 && Jets[i].eta() > -3)
            JetCount30 = JetCount30 + 1;
      HJetCount30.Fill(JetCount30);
      // cout << JetCount30 << endl;

      // End of event loop.
   }

   // Final statistics.
   pythia.statistics(); 

   // Histograms
   PsFileHelper PsFile("XD.ps");
   PsFile.AddTextPage("XD");
   PsFile.AddPlot(HJetCount30, "hist text", true);
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // Cleanup
   out.close();

   // Done.
   return 0; 
}

