#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "Pythia.h"
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

#include "SetStyle.h"
#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"

int main(int argc, char *argv[])
{
   /*
   if(argc < 2)
   {
      cerr << "Usage " << argv[0] << " output" << endl;
      return -1;
   }
   */

   SetStyle();

   // TFile OutputFile(argv[1], "RECREATE");

   TH1D HNuNuMass("HNuNuMass", "nunu mass;Mass [GeV]", 100, 0, 150);
   TH1D HNuNuAngle("HNuNuAngle", "nunu angle;Angle", 100, -3.2, 3.2);
   TH1D HNuP("HNuP", "nu momentum;P [GeV]", 100, 0, 150);
   TH1D HNuPT("HNuPT", "nu transverse momentum;P [GeV]", 100, 0, 150);
   TH1D HNuEta("HNuEta", "nu eta", 100, -5, 5);
   TH1D HNuNuPT("HNuNuPT", "nunu transverse momentum;P [GeV]", 100, 0, 150);
   TH2D HNuPTPT("HNuPTPT", "PT vs. PT", 100, 0, 150, 100, 0, 150);

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("WeakSingleBoson:ffbar2gmZ = on");    // Switch on Z
   pythia.readString("WeakSingleBoson:ffbar2W = off");     // Switch off W
   pythia.readString("23:oneChannel = 1 1 0 16 -16");      // Force Z to decay to neutrinos

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   int TotalEntry = 20000;
   for(int iEntry = 0; iEntry < TotalEntry; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << TotalEntry << endl;

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
         Particles[j].StatusCode = pythia.event.statusHepMC(j);

         Particles[j].Mothers = pythia.event.motherList(j);
         Particles[j].Daughters = pythia.event.daughterList(j);
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // neutrino distributions
      int GoodLeptonCount = 0;
      FourVector Nu1P, Nu2P;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].PDGID != 16 && Tree[i].PDGID != -16)   // note that we force Z decay to tau neutrino
            continue;

         if(Tree[i].Mothers.size() == 0)
            continue;

         bool ZMother = false;
         for(int j = 0; j < (int)Tree[i].Mothers.size(); j++)
            if(Tree[Tree[i].Mothers[j]].PDGID == 23)
               ZMother = true;
         if(ZMother == false)
            continue;

         if(Tree[i].PDGID == 16)
            Nu1P = FourVector(Tree[i].P);
         if(Tree[i].PDGID == -16)
            Nu2P = FourVector(Tree[i].P);

         if(FourVector(Tree[i].P).GetAbsEta() > 3)
            continue;
         if(FourVector(Tree[i].P).GetPT() < 20)
            continue;

         GoodLeptonCount = GoodLeptonCount + 1;
      }

      HNuNuMass.Fill((Nu1P + Nu2P).GetMass());
      HNuNuAngle.Fill(GetAngle(Nu1P, Nu2P));
      HNuP.Fill(Nu1P.GetP());       HNuP.Fill(Nu2P.GetP());
      HNuPT.Fill(Nu1P.GetPT());     HNuPT.Fill(Nu2P.GetPT());
      HNuEta.Fill(Nu1P.GetEta());   HNuEta.Fill(Nu2P.GetEta());
      HNuNuPT.Fill((Nu1P + Nu2P).GetPT());
      HNuPTPT.Fill(Nu1P.GetPT(), Nu2P.GetPT());

      /*
      // Group into jets - also calculate MET along the way
      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // final particles only
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16 || Tree[i].PDGID == 14 || Tree[i].PDGID == -14
            || Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(Tree[i].P).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(Tree[i].P).GetPT() < 1)   // mini particles - forget it
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         MissingEnergy = MissingEnergy - FourVector(Tree[i].P);
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.5

      vector<FourVector> GoodJets;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 40)
            continue;
         GoodJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));
      }
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      if(GoodJets.size() < 2 || Groups.size() < 2)
         continue;

      double MR = Get2011MR(Groups[0], Groups[1]);
      double R = Get2011R(Groups[0], Groups[1], MissingEnergy);
      */
   }

   PsFileHelper PsFile("Yay.ps");
   PsFile.AddTextPage("Yaya");

   PsFile.AddPlot(HNuNuMass, "", true);
   PsFile.AddPlot(HNuNuAngle, "", true);
   PsFile.AddPlot(HNuP, "", true);
   PsFile.AddPlot(HNuPT, "", true);
   PsFile.AddPlot(HNuEta, "", true);
   PsFile.AddPlot(HNuNuPT, "", true);
   PsFile.AddPlot(HNuPTPT, "colz", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   // OutputFile.Close();

   return 0;
}

