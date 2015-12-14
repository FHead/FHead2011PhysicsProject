#include <iostream>
#include <string>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TObject.h"
#include "TClonesArray.h"

#include "ExRootTreeReader.h"
#include "ExRootTreeWriter.h"
#include "ExRootTreeBranch.h"
#include "BlockClasses.h"
#include "TSimpleArray.h"

int main(int argc, char *argv[])
{
   string InputFileName = "ZnunuJet.root";
   string OutputFileName = "Test.root";

   TChain InputTree("GEN", "GEN");
   InputTree.AddFile(InputFileName.c_str());

   int ParticleCount = 0;
   InputTree.SetBranchAddress("Particle_size", &ParticleCount);

   TClonesArray *Array = NULL;
   InputTree.SetBranchAddress("Particle", &Array);

   TFile OutputFile(OutputFileName.c_str(), "recreate");

   TTree OutputTree("DelphesPlainTree", "Delphes plain tree");

   OutputTree.Branch("ParticleCount", &ParticleCount, "ParticleCount/I");

   double E[1000], Px[1000], Py[1000], Pz[1000];
   OutputTree.Branch("E", E, "E[1000]/D");
   OutputTree.Branch("Px", Px, "Px[1000]/D");
   OutputTree.Branch("Py", Py, "Py[1000]/D");
   OutputTree.Branch("Pz", Pz, "Pz[1000]/D");

   double Eta[1000], Phi[1000], PT[1000];
   // OutputTree.Branch("Eta", Eta, "Eta[1000]/D");
   // OutputTree.Branch("Phi", Phi, "Phi[1000]/D");
   // OutputTree.Branch("PT", PT, "PT[1000]/D");

   int PDGID[1000], Status[1000], M1[1000], M2[1000], D1[1000], D2[1000];
   OutputTree.Branch("PDGID", PDGID, "PDGID[1000]/I");
   OutputTree.Branch("Status", Status, "Status[1000]/I");
   OutputTree.Branch("M1", M1, "M1[1000]/I");
   OutputTree.Branch("M2", M2, "M2[1000]/I");
   OutputTree.Branch("D1", D1, "D1[1000]/I");
   OutputTree.Branch("D2", D2, "D2[1000]/I");

   double Charge[1000], T[1000], X[1000], Y[1000], Z[1000], M[1000];
   OutputTree.Branch("Charge", Charge, "Charge[1000]/D");
   // OutputTree.Branch("T", T, "T[1000]/D");
   // OutputTree.Branch("X", X, "X[1000]/D");
   // OutputTree.Branch("Y", Y, "Y[1000]/D");
   // OutputTree.Branch("Z", Z, "Z[1000]/D");
   // OutputTree.Branch("M", M, "M[1000]/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      if(ParticleCount == 0)   // rejected event
         continue;

      for(int i = 0; i < ParticleCount; i++)
      {
         TRootC::GenParticle *Particle = (TRootC::GenParticle *)Array->At(i);

         E[i] = Particle->E;
         Px[i] = Particle->Px;
         Py[i] = Particle->Py;
         Pz[i] = Particle->Pz;
         Eta[i] = Particle->Eta;
         Phi[i] = Particle->Phi;
         PT[i] = Particle->PT;
         PDGID[i] = Particle->PID;
         Status[i] = Particle->Status;
         M1[i] = Particle->M1;
         M2[i] = Particle->M2;
         D1[i] = Particle->D1;
         D2[i] = Particle->D2;
         Charge[i] = Particle->Charge;
         T[i] = Particle->T;
         X[i] = Particle->X;
         Y[i] = Particle->Y;
         Z[i] = Particle->Z;
         M[i] = Particle->M;
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

