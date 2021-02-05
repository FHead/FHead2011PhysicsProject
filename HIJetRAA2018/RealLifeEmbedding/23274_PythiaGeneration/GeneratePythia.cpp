#include <string>
#include <vector>
#include <sstream>
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

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper4.h"
#include "GenparticleTree3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "CustomAssert.h"

#define MAX 10000

int main(int argc, char *argv[]);
void GenerateEvents(string OutputFileName, int NEvent, double PTHat);
double DrawMomentum(double Mean);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string OutputFileName = CL.Get("Output");
   int N                 = CL.GetInt("N", 1000);
   double PTHat          = CL.GetDouble("PTHat", 100);

   GenerateEvents(OutputFileName, N, PTHat);

   return 0;
}

void GenerateEvents(string OutputFileName, int NEvent, double PTHat)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   int EventNo = 0;
   int RunNo = 1;
   int year = 2020;
   int subDir = 827;
   int process = 0;
   bool isMC = true;
   double BoostGamma = 1.0;

   int nParticle;
   float e[MAX];
   float px[MAX];
   float py[MAX];
   float pz[MAX];
   float pt[MAX];
   float pmag[MAX];
   float rap[MAX];
   float eta[MAX];
   float theta[MAX];
   float phi[MAX];
   float mass[MAX];
   int subevent[MAX];
   // charge, pwflag
   int pid[MAX];
   int status[MAX];
   float vx[MAX];
   float vy[MAX];
   float vz[MAX];

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("tgen", "Tree! ®");

   OutputTree.Branch("EventNo", &EventNo, "EventNo/I");
   OutputTree.Branch("RunNo", &RunNo, "RunNo/I");
   OutputTree.Branch("year", &year, "year/I");
   OutputTree.Branch("subDir", &subDir, "subDir/I");
   OutputTree.Branch("process", &process, "process/I");
   OutputTree.Branch("isMC", &isMC, "isMC/O");

   OutputTree.Branch("nParticle", &nParticle, "nParticle/I");
   OutputTree.Branch("e", &e, "e[nParticle]/F");
   OutputTree.Branch("px", &px, "px[nParticle]/F");
   OutputTree.Branch("py", &py, "py[nParticle]/F");
   OutputTree.Branch("pz", &pz, "pz[nParticle]/F");
   OutputTree.Branch("pt", &pt, "pt[nParticle]/F");
   OutputTree.Branch("pmag", &pmag, "pmag[nParticle]/F");
   OutputTree.Branch("rap", &rap, "rap[nParticle]/F");
   OutputTree.Branch("eta", &eta, "eta[nParticle]/F");
   OutputTree.Branch("theta", &theta, "theta[nParticle]/F");
   OutputTree.Branch("phi", &phi, "phi[nParticle]/F");
   OutputTree.Branch("mass", &mass, "mass[nParticle]/F");
   OutputTree.Branch("subevent", &subevent, "subevent[nParticle]/I");
   OutputTree.Branch("pid", &pid, "pid[nParticle]/I");
   OutputTree.Branch("status", &status, "status[nParticle]/I");
   OutputTree.Branch("vx", &vx, "vx[nParticle]/F");
   OutputTree.Branch("vy", &vy, "vy[nParticle]/F");
   OutputTree.Branch("vz", &vz, "vz[nParticle]/F");

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Tune:pp 14");                        // Tune?  What??
   pythia.readString("Tune:ee 7");                         // I see this in CMS production settings.....

   pythia.readString("HardQCD:all = on");
   pythia.readString(Form("PhaseSpace:pTHatMin = %f", PTHat));

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.readString("Beams:idA = 2212");                  // proton
   pythia.readString("Beams:idB = 2212");                  // proton
   pythia.readString("Beams:eCM = 5020");                  // Collision energy: 5020 GeV

   pythia.readString("Next:numberCount = 0");              // how often to print to screen on progress
   pythia.readString("Next:numberShowProcess = 0");        // do we print first hard process?  No!
   pythia.readString("Next:numberShowEvent = 0");          // do we print first event?  No!

   pythia.init();

   for(int iEntry = 0; iEntry < NEvent; iEntry++)
   {
      EventNo = iEntry;

      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << NEvent << endl;

      vector<GenParticle> Particles;
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // Generate event
      pythia.next();

      // Particles
      Particles.clear();
      Particles.resize(pythia.event.size());

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
      Tree.Initialize(Particles);

      // Write particles into tree
      nParticle = pythia.event.size();

      // Finally, write everything out
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         e[i]        = Tree[i].P[0];
         px[i]       = Tree[i].P[1];
         py[i]       = Tree[i].P[2];
         pz[i]       = Tree[i].P[3];
         pt[i]       = Tree[i].P.GetPT();
         pmag[i]     = Tree[i].P.GetP();
         rap[i]      = Tree[i].P.GetY();
         eta[i]      = Tree[i].P.GetEta();
         theta[i]    = Tree[i].P.GetTheta();
         phi[i]      = Tree[i].P.GetPhi();
         mass[i]     = Tree[i].P.GetMass();
         subevent[i] = 0;
         pid[i]      = Tree[i].PDGID;
         status[i]   = Tree[i].StatusCode;
         vx[i]       = Tree[i].V[1];
         vy[i]       = Tree[i].V[2];
         vz[i]       = Tree[i].V[3];
      }

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();
}

