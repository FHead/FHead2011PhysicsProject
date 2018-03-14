using namespace std;

#include "TreeMessenger.h"


TreeMessenger::TreeMessenger()
{
   Initialize(NULL);
}

TreeMessenger::TreeMessenger(TFile &File, string TreeName)
{
   Initialize((TTree *)File.Get(TreeName.c_str()));
}

TreeMessenger::TreeMessenger(TTree *TreePointer)
{
   Initialize(Tree);
}

void TreeMessenger::Initialize(TTree *TreePointer)
{
   Tree = TreePointer;
   if(Tree == NULL)
      return;
   
   Tree->SetBranchAddress("nev", &nev);
   Tree->SetBranchAddress("Bgen", &Bgen);
   Tree->SetBranchAddress("Sigin", &Sigin);
   Tree->SetBranchAddress("Sigjet", &Sigjet);
   Tree->SetBranchAddress("Ntot", &Ntot);
   Tree->SetBranchAddress("Nhyd", &Nhyd);
   Tree->SetBranchAddress("Npyt", &Npyt);
   Tree->SetBranchAddress("Njet", &Njet);
   Tree->SetBranchAddress("Nbcol", &Nbcol);
   Tree->SetBranchAddress("Npart", &Npart);
   Tree->SetBranchAddress("Px", &Px);
   Tree->SetBranchAddress("Py", &Py);
   Tree->SetBranchAddress("Pz", &Pz);
   Tree->SetBranchAddress("E", &E);
   Tree->SetBranchAddress("X", &X);
   Tree->SetBranchAddress("Y", &Y);
   Tree->SetBranchAddress("Z", &Z);
   Tree->SetBranchAddress("T", &T);
   Tree->SetBranchAddress("pdg", &pdg);
   Tree->SetBranchAddress("Mpdg", &Mpdg);
   Tree->SetBranchAddress("type", &type);
   Tree->SetBranchAddress("pythiaStatus", &pythiaStatus);
   Tree->SetBranchAddress("Index", &Index);
   Tree->SetBranchAddress("MotherIndex", &MotherIndex);
   Tree->SetBranchAddress("NDaughters", &NDaughters);
   Tree->SetBranchAddress("FirstDaughterIndex", &FirstDaughterIndex);
   Tree->SetBranchAddress("LastDaughterIndex", &LastDaughterIndex);
   Tree->SetBranchAddress("final", &Final);
}

int TreeMessenger::EntryCount()
{
   if(Tree == NULL)
      return -1;
   return Tree->GetEntries();
}

bool TreeMessenger::GetEntry(int Entry)
{
   if(Tree == NULL)
      return false;
   if(Entry < 0 || Entry >= EntryCount())
      return false;
   
   Tree->GetEntry(Entry);
   return true;
}


