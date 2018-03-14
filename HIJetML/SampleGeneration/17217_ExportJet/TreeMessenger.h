#include <iostream>

#include "TFile.h"
#include "TTree.h"

#define TREEMAX 200000

class TreeMessenger
{
public:
   TTree *Tree;
   int   nev;
   float Bgen;
   float Sigin;
   float Sigjet;
   int   Ntot;
   int   Nhyd;
   int   Npyt;
   int   Njet;
   int   Nbcol;
   int   Npart;
   float Px[TREEMAX];
   float Py[TREEMAX];
   float Pz[TREEMAX];
   float E[TREEMAX];
   float X[TREEMAX];
   float Y[TREEMAX];
   float Z[TREEMAX];
   float T[TREEMAX];
   int   pdg[TREEMAX];
   int   Mpdg[TREEMAX];
   int   type[TREEMAX];
   int   pythiaStatus[TREEMAX];
   int   Index[TREEMAX];
   int   MotherIndex[TREEMAX];
   int   NDaughters[TREEMAX];
   int   FirstDaughterIndex[TREEMAX];
   int   LastDaughterIndex[TREEMAX];
   int   Final[TREEMAX];
public:
   TreeMessenger();
   TreeMessenger(TFile &File, std::string TreeName = "td");
   TreeMessenger(TTree *TreePointer);
   void Initialize(TTree *TreePointer);
   int EntryCount();
   bool GetEntry(int Entry);
};





