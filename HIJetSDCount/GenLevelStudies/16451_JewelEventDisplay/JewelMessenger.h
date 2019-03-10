#ifndef JewelMessenger_H_16451
#define JewelMessenger_H_16451

#include "TFile.h"
#include "TTree.h"

#define JEWEL_PARTICLE_MAX 10000

class JewelMessenger
{
public:
   TTree *Tree;
   int ParticleCount;
   int PID[JEWEL_PARTICLE_MAX];
   double PX[JEWEL_PARTICLE_MAX];
   double PY[JEWEL_PARTICLE_MAX];
   double PZ[JEWEL_PARTICLE_MAX];
   double E[JEWEL_PARTICLE_MAX];
   double M[JEWEL_PARTICLE_MAX];
   double Status[JEWEL_PARTICLE_MAX];
   double Weight;
public:
   JewelMessenger(TFile &F);
   JewelMessenger(TFile *F);
   void SetBranchAddress();
   int EntryCount();
   void GetEntry(int iE);
};

JewelMessenger::JewelMessenger(TFile &F)
   : Tree(NULL)
{
   Tree = (TTree *)F.Get("Tree");
   if(Tree == NULL)
      return;

   SetBranchAddress();
}

JewelMessenger::JewelMessenger(TFile *F)
   : Tree(NULL)
{
   if(F == NULL)
      return;

   Tree = (TTree *)F->Get("Tree");
   if(Tree == NULL)
      return;

   SetBranchAddress();
}

void JewelMessenger::SetBranchAddress()
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("NP", &ParticleCount);
   Tree->SetBranchAddress("PID", &PID);
   Tree->SetBranchAddress("PX", &PX);
   Tree->SetBranchAddress("PY", &PY);
   Tree->SetBranchAddress("PZ", &PZ);
   Tree->SetBranchAddress("PE", &E);
   Tree->SetBranchAddress("PM", &M);
   Tree->SetBranchAddress("PStatus", &Status);
   Tree->SetBranchAddress("EWeight", &Weight);
}

int JewelMessenger::EntryCount()
{
   if(Tree != NULL)
      return Tree->GetEntries();
   return 0;
}

void JewelMessenger::GetEntry(int iE)
{
   if(Tree == NULL)
      return;

   Tree->GetEntry(iE);
}

#endif


