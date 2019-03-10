#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "Pythia8/Pythia.h"
using namespace Pythia8;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper3.h"
#include "GenparticleTree.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile OutputFile("/tmp/chenyi/Output.root", "RECREATE");

   int Treenev;
   int TreeNtot;
   float TreePx[10000];
   float TreePy[10000];
   float TreePz[10000];
   float TreeE[10000];
   float TreeX[10000];
   float TreeY[10000];
   float TreeZ[10000];
   float TreeT[10000];
   int Treepdg[10000];
   int TreeMpdg[10000];
   int Treetype[10000];
   int TreepythiaStatus[10000];
   int TreeIndex[10000];
   int TreeMotherIndex[10000];
   int TreeNDaughters[10000];
   int TreeFirstDaughterIndex[10000];
   int TreeLastDaughterIndex[10000];
   int Treefinal[10000];

   TTree Tree("td", "td");
   
   Tree.Branch("nev", &Treenev, "nev/I");
   Tree.Branch("Ntot", &TreeNtot, "Ntot/I");
   Tree.Branch("Px", &TreePx, "Px[Ntot]/F");
   Tree.Branch("Py", &TreePy, "Py[Ntot]/F");
   Tree.Branch("Pz", &TreePz, "Pz[Ntot]/F");
   Tree.Branch("E", &TreeE, "E[Ntot]/F");
   Tree.Branch("X", &TreeX, "X[Ntot]/F");
   Tree.Branch("Y", &TreeY, "Y[Ntot]/F");
   Tree.Branch("Z", &TreeZ, "Z[Ntot]/F");
   Tree.Branch("T", &TreeT, "T[Ntot]/F");
   Tree.Branch("pdg", &Treepdg, "pdg[Ntot]/I");
   Tree.Branch("Mpdg", &TreeMpdg, "Mpdg[Ntot]/I");
   Tree.Branch("type", &Treetype, "type[Ntot]/I");
   Tree.Branch("pythiaStatus", &TreepythiaStatus, "pythiaStatus[Ntot]/I");
   Tree.Branch("Index", &TreeIndex, "Index[Ntot]/I");
   Tree.Branch("MotherIndex", &TreeMotherIndex, "MotherIndex[Ntot]/I");
   Tree.Branch("NDaughters", &TreeNDaughters, "NDaughters[Ntot]/I");
   Tree.Branch("FirstDaughterIndex", &TreeFirstDaughterIndex, "FirstDaughterIndex[Ntot]/I");
   Tree.Branch("LastDaughterIndex", &TreeLastDaughterIndex, "LastDaughterIndex[Ntot]/I");
   Tree.Branch("final", &Treefinal, "final[Ntot]/I");

   Pythia pythia;

   pythia.readString("HardQCD:all = on");                  // 2 -> 2 processes
   pythia.readString("PhaseSpace:pTHatMin = 120");         // PTHat > 120

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.readString("Beams:eCM = 5020");                  // Proton-proton collision at 5.02 TeV

   pythia.init();

   int TotalEntry = 60000;
   for(int iEntry = 0; iEntry < TotalEntry; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry " << iEntry + 1 << "/" << TotalEntry << endl;

      // Generate event
      pythia.next();

      // Start to export stuff
      Treenev = iEntry;
      TreeNtot = pythia.event.size();
      
      // Loop over particles
      for(int j = 0; j < pythia.event.size(); j++)
      {
         TreeE[j] = pythia.event[j].e();
         TreePx[j] = pythia.event[j].px();
         TreePy[j] = pythia.event[j].py();
         TreePz[j] = pythia.event[j].pz();
         
         TreeT[j] = pythia.event[j].tProd();
         TreeX[j] = pythia.event[j].xProd();
         TreeY[j] = pythia.event[j].yProd();
         TreeZ[j] = pythia.event[j].zProd();

         Treepdg[j] = pythia.event[j].id();
         TreeMpdg[j] = -1;
         TreepythiaStatus[j] = pythia.event[j].statusHepMC();

         TreeIndex[j] = j;

         if(pythia.event[j].motherList().size() == 0)
            TreeMotherIndex[j] = -1;
         else
            TreeMotherIndex[j] = pythia.event[j].motherList()[0];

         TreeNDaughters[j] = pythia.event[j].daughterList().size();
         if(TreeNDaughters[j] == 0)
         {
            TreeFirstDaughterIndex[j] = -1;
            TreeLastDaughterIndex[j] = -1;
         }
         else
         {
            TreeFirstDaughterIndex[j] = pythia.event[j].daughterList().front();
            TreeLastDaughterIndex[j] = pythia.event[j].daughterList().back();
         }

         Treefinal[j] = pythia.event[j].isFinal();
      }

      Tree.Fill();
   }

   Tree.Write();

   OutputFile.Close();

   return 0;
}

