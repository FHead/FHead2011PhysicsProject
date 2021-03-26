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

TreeMessenger::~TreeMessenger()
{
   if(Px != nullptr)   delete[] Px;
   if(Py != nullptr)   delete[] Py;
   if(Pz != nullptr)   delete[] Pz;
   if(E != nullptr)   delete[] E;
   if(X != nullptr)   delete[] X;
   if(Y != nullptr)   delete[] Y;
   if(Z != nullptr)   delete[] Z;
   if(T != nullptr)   delete[] T;
   if(pdg != nullptr)   delete[] pdg;
   if(Mpdg != nullptr)   delete[] Mpdg;
   if(type != nullptr)   delete[] type;
   if(pythiaStatus != nullptr)   delete[] pythiaStatus;
   if(Index != nullptr)   delete[] Index;
   if(MotherIndex != nullptr)   delete[] MotherIndex;
   if(NDaughters != nullptr)   delete[] NDaughters;
   if(FirstDaughterIndex != nullptr)   delete[] FirstDaughterIndex;
   if(LastDaughterIndex != nullptr)   delete[] LastDaughterIndex;
   if(Final != nullptr)   delete[] Final;
}

void TreeMessenger::Initialize(TTree *TreePointer)
{
   Px = nullptr;
   Py = nullptr;
   Pz = nullptr;
   E = nullptr;
   X = nullptr;
   Y = nullptr;
   Z = nullptr;
   T = nullptr;
   pdg = nullptr;
   Mpdg = nullptr;
   type = nullptr;
   pythiaStatus = nullptr;
   Index = nullptr;
   MotherIndex = nullptr;
   NDaughters = nullptr;
   FirstDaughterIndex = nullptr;
   LastDaughterIndex = nullptr;
   Final = nullptr;
   
   Tree = TreePointer;
   if(Tree == NULL)
      return;
   
   Px = new float[TREEMAX];
   Py = new float[TREEMAX];
   Pz = new float[TREEMAX];
   E = new float[TREEMAX];
   X = new float[TREEMAX];
   Y = new float[TREEMAX];
   Z = new float[TREEMAX];
   T = new float[TREEMAX];
   pdg = new int[TREEMAX];
   Mpdg = new int[TREEMAX];
   type = new int[TREEMAX];
   pythiaStatus = new int[TREEMAX];
   Index = new int[TREEMAX];
   MotherIndex = new int[TREEMAX];
   NDaughters = new int[TREEMAX];
   FirstDaughterIndex = new int[TREEMAX];
   LastDaughterIndex = new int[TREEMAX];
   Final = new int[TREEMAX];

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
   Tree->SetBranchAddress("Px", Px);
   Tree->SetBranchAddress("Py", Py);
   Tree->SetBranchAddress("Pz", Pz);
   Tree->SetBranchAddress("E", E);
   Tree->SetBranchAddress("X", X);
   Tree->SetBranchAddress("Y", Y);
   Tree->SetBranchAddress("Z", Z);
   Tree->SetBranchAddress("T", T);
   Tree->SetBranchAddress("pdg", pdg);
   Tree->SetBranchAddress("Mpdg", Mpdg);
   Tree->SetBranchAddress("type", type);
   Tree->SetBranchAddress("pythiaStatus", pythiaStatus);
   Tree->SetBranchAddress("Index", Index);
   Tree->SetBranchAddress("MotherIndex", MotherIndex);
   Tree->SetBranchAddress("NDaughters", NDaughters);
   Tree->SetBranchAddress("FirstDaughterIndex", FirstDaughterIndex);
   Tree->SetBranchAddress("LastDaughterIndex", LastDaughterIndex);
   Tree->SetBranchAddress("final", Final);
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


