//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 17 16:29:41 2020 by ROOT version 6.12/07
// from TTree hi/Tree of Hi gen Event
// found on file: Data2018/200817_120224/0000/HiForestAOD_415.root
//////////////////////////////////////////////////////////

#ifndef Gen_h
#define Gen_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class Gen {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           event;
   Float_t         b;
   Float_t         npart;
   Float_t         ncoll;
   Float_t         nhard;
   Float_t         phi0;
   Float_t         scale;
   Int_t           n[3];
   Float_t         ptav[3];
   Int_t           mult;
   vector<float>   *pt;
   vector<float>   *eta;
   vector<float>   *phi;
   vector<int>     *pdg;
   vector<int>     *chg;
   vector<int>     *matchingID;
   vector<int>     *nMothers;
   vector<vector<int> > *motherIdx;
   vector<int>     *nDaughters;
   vector<vector<int> > *daughterIdx;
   vector<int>     *sube;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Float_t         vr;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_b;   //!
   TBranch        *b_npart;   //!
   TBranch        *b_ncoll;   //!
   TBranch        *b_nhard;   //!
   TBranch        *b_phi0;   //!
   TBranch        *b_scale;   //!
   TBranch        *b_n;   //!
   TBranch        *b_ptav;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_eta;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_pdg;   //!
   TBranch        *b_chg;   //!
   TBranch        *b_matchingID;   //!
   TBranch        *b_nMothers;   //!
   TBranch        *b_motherIdx;   //!
   TBranch        *b_nDaughters;   //!
   TBranch        *b_daughterIdx;   //!
   TBranch        *b_sube;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_vr;   //!

   Gen(TTree *tree=0);
   virtual ~Gen();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Gen_cxx
Gen::Gen(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Data2018/200817_120224/0000/HiForestAOD_415.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Data2018/200817_120224/0000/HiForestAOD_415.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("Data2018/200817_120224/0000/HiForestAOD_415.root:/HiGenParticleAna");
      dir->GetObject("hi",tree);

   }
   Init(tree);
}

Gen::~Gen()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Gen::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Gen::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Gen::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pt = 0;
   eta = 0;
   phi = 0;
   pdg = 0;
   chg = 0;
   matchingID = 0;
   nMothers = 0;
   motherIdx = 0;
   nDaughters = 0;
   daughterIdx = 0;
   sube = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("npart", &npart, &b_npart);
   fChain->SetBranchAddress("ncoll", &ncoll, &b_ncoll);
   fChain->SetBranchAddress("nhard", &nhard, &b_nhard);
   fChain->SetBranchAddress("phi0", &phi0, &b_phi0);
   fChain->SetBranchAddress("scale", &scale, &b_scale);
   fChain->SetBranchAddress("n", n, &b_n);
   fChain->SetBranchAddress("ptav", ptav, &b_ptav);
   fChain->SetBranchAddress("mult", &mult, &b_mult);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("eta", &eta, &b_eta);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("pdg", &pdg, &b_pdg);
   fChain->SetBranchAddress("chg", &chg, &b_chg);
   fChain->SetBranchAddress("matchingID", &matchingID, &b_matchingID);
   fChain->SetBranchAddress("nMothers", &nMothers, &b_nMothers);
   fChain->SetBranchAddress("motherIdx", &motherIdx, &b_motherIdx);
   fChain->SetBranchAddress("nDaughters", &nDaughters, &b_nDaughters);
   fChain->SetBranchAddress("daughterIdx", &daughterIdx, &b_daughterIdx);
   fChain->SetBranchAddress("sube", &sube, &b_sube);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("vr", &vr, &b_vr);
   Notify();
}

Bool_t Gen::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Gen::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Gen::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Gen_cxx
