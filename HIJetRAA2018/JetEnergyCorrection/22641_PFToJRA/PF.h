//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 17 16:23:50 2020 by ROOT version 6.12/07
// from TTree pfTree/pf candidate tree
// found on file: Data2018/200817_120224/0000/HiForestAOD_415.root
//////////////////////////////////////////////////////////

#ifndef PF_h
#define PF_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class PF {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nPFpart;
   vector<int>     *pfId;
   vector<float>   *pfPt;
   vector<float>   *pfEnergy;
   vector<float>   *pfEta;
   vector<float>   *pfPhi;
   vector<float>   *pfM;
   vector<float>   *pfEcalE;
   vector<float>   *pfEcalEraw;
   vector<float>   *pfHcalE;
   vector<float>   *pfHcalEraw;
   vector<int>     *trkAlgo;
   vector<float>   *trkPtError;
   vector<float>   *trkNHit;
   vector<float>   *trkChi2;
   vector<float>   *trkNdof;

   // List of branches
   TBranch        *b_nPFpart;   //!
   TBranch        *b_pfId;   //!
   TBranch        *b_pfPt;   //!
   TBranch        *b_pfEnergy;   //!
   TBranch        *b_pfEta;   //!
   TBranch        *b_pfPhi;   //!
   TBranch        *b_pfM;   //!
   TBranch        *b_pfEcalE;   //!
   TBranch        *b_pfEcalEraw;   //!
   TBranch        *b_pfHcalE;   //!
   TBranch        *b_pfHcalEraw;   //!
   TBranch        *b_trkAlgo;   //!
   TBranch        *b_trkPtError;   //!
   TBranch        *b_trkNHit;   //!
   TBranch        *b_trkChi2;   //!
   TBranch        *b_trkNdof;   //!

   PF(TTree *tree=0);
   virtual ~PF();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PF_cxx
PF::PF(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Data2018/200817_120224/0000/HiForestAOD_415.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Data2018/200817_120224/0000/HiForestAOD_415.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("Data2018/200817_120224/0000/HiForestAOD_415.root:/pfcandAnalyzer");
      dir->GetObject("pfTree",tree);

   }
   Init(tree);
}

PF::~PF()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PF::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PF::LoadTree(Long64_t entry)
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

void PF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pfId = 0;
   pfPt = 0;
   pfEnergy = 0;
   pfEta = 0;
   pfPhi = 0;
   pfM = 0;
   pfEcalE = 0;
   pfEcalEraw = 0;
   pfHcalE = 0;
   pfHcalEraw = 0;
   trkAlgo = 0;
   trkPtError = 0;
   trkNHit = 0;
   trkChi2 = 0;
   trkNdof = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nPFpart", &nPFpart, &b_nPFpart);
   fChain->SetBranchAddress("pfId", &pfId, &b_pfId);
   fChain->SetBranchAddress("pfPt", &pfPt, &b_pfPt);
   fChain->SetBranchAddress("pfEnergy", &pfEnergy, &b_pfEnergy);
   fChain->SetBranchAddress("pfEta", &pfEta, &b_pfEta);
   fChain->SetBranchAddress("pfPhi", &pfPhi, &b_pfPhi);
   fChain->SetBranchAddress("pfM", &pfM, &b_pfM);
   fChain->SetBranchAddress("pfEcalE", &pfEcalE, &b_pfEcalE);
   fChain->SetBranchAddress("pfEcalEraw", &pfEcalEraw, &b_pfEcalEraw);
   fChain->SetBranchAddress("pfHcalE", &pfHcalE, &b_pfHcalE);
   fChain->SetBranchAddress("pfHcalEraw", &pfHcalEraw, &b_pfHcalEraw);
   fChain->SetBranchAddress("trkAlgo", &trkAlgo, &b_trkAlgo);
   fChain->SetBranchAddress("trkPtError", &trkPtError, &b_trkPtError);
   fChain->SetBranchAddress("trkNHit", &trkNHit, &b_trkNHit);
   fChain->SetBranchAddress("trkChi2", &trkChi2, &b_trkChi2);
   fChain->SetBranchAddress("trkNdof", &trkNdof, &b_trkNdof);
   Notify();
}

Bool_t PF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PF::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PF::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PF_cxx
