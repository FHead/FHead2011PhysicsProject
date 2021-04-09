#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#define MAX 50000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   ifstream InputFile(InputFileName);

   bool IsMC = true;
   int CurrentEvent = -1;
   int NParticle = 0;
   float PX[MAX], PY[MAX], PZ[MAX];
   float PT[MAX], PMag[MAX], PRap[MAX];
   float PEta[MAX], PTheta[MAX], PPhi[MAX], PMass[MAX];

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("tgan", "Particles from GAN network");

   Tree.Branch("isMC",      &IsMC,         "isMC/O");
   Tree.Branch("EventNo",   &CurrentEvent, "EventNo/I");
   Tree.Branch("nParticle", &NParticle,    "nParticle/I");
   Tree.Branch("px",        &PX,           "px[nParticle]/F");
   Tree.Branch("py",        &PY,           "py[nParticle]/F");
   Tree.Branch("pz",        &PZ,           "pz[nParticle]/F");
   Tree.Branch("pt",        &PT,           "pt[nParticle]/F");
   Tree.Branch("pmag",      &PMag,         "pmag[nParticle]/F");
   Tree.Branch("rap",       &PRap,         "rap[nParticle]/F");
   Tree.Branch("eta",       &PEta,         "eta[nParticle]/F");
   Tree.Branch("theta",     &PTheta,       "theta[nParticle]/F");
   Tree.Branch("phi",       &PPhi,         "phi[nParticle]/F");
   Tree.Branch("mass",      &PMass,        "mass[nParticle]/F");

   while(InputFile)
   {
      char ch[10240];
      ch[0] = '\0';
      InputFile.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      for(int i = 0; ch[i] != '\0'; i++)
         if(ch[i] == ',')
            ch[i] = ' ';

      stringstream str(ch);

      int NewEvent = -1;
      str >> NewEvent;
      if(NewEvent < 0)
         continue;

      double X = 0, Y = 0, Z = 0, M = -1;
      str >> X >> Y >> Z >> M;
      if(M < 0)
         continue;

      if(CurrentEvent < 0)
      {
         NParticle = 0;
         CurrentEvent = NewEvent;
      }
      else if(NewEvent != CurrentEvent)
      {
         Tree.Fill();
         CurrentEvent = NewEvent;
         NParticle = 0;
      }

      FourVector P(0, X, Y, Z);
      P[0] = sqrt(P.GetP() * P.GetP() + M * M);

      PX[NParticle] = X;
      PY[NParticle] = Y;
      PZ[NParticle] = Z;
      PT[NParticle] = P.GetPT();
      PMag[NParticle] = P.GetP();
      PRap[NParticle] = P.GetRapidity();
      PEta[NParticle] = P.GetEta();
      PTheta[NParticle] = P.GetTheta();
      PPhi[NParticle] = P.GetPhi();
      PMass[NParticle] = M;
      NParticle = NParticle + 1;
   }

   Tree.Fill();

   Tree.Write();
   OutputFile.Close();

   InputFile.close();

   return 0;
}





