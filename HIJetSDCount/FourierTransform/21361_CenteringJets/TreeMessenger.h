#include <iostream>

#include "TFile.h"
#include "TTree.h"

#define TREEMAX 100000

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
   float *Px;
   float *Py;
   float *Pz;
   float *E;
   float *X;
   float *Y;
   float *Z;
   float *T;
   int   *pdg;
   int   *Mpdg;
   int   *type;
   int   *pythiaStatus;
   int   *Index;
   int   *MotherIndex;
   int   *NDaughters;
   int   *FirstDaughterIndex;
   int   *LastDaughterIndex;
   int   *Final;
public:
   TreeMessenger();
   TreeMessenger(TFile &File, std::string TreeName = "td");
   TreeMessenger(TTree *TreePointer);
   ~TreeMessenger();
   void Initialize(TTree *TreePointer);
   int EntryCount();
   bool GetEntry(int Entry);
};





