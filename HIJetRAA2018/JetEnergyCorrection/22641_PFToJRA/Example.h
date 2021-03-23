//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 17 15:52:15 2020 by ROOT version 6.12/07
// from TTree t/t
// found on file: JRAExample.root
//////////////////////////////////////////////////////////

#ifndef Example_h
#define Example_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class Example {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<int>     *npus;
   vector<float>   *tnpus;
   vector<float>   *zpositions;
   vector<int>     *bxns;
   vector<float>   *sumpt_lowpt;
   vector<float>   *sumpt_highpt;
   vector<int>     *ntrks_lowpt;
   vector<int>     *ntrks_highpt;
   vector<float>   *rhos;
   Float_t         rho;
   Float_t         pthat;
   Float_t         beta;
   Float_t         betaStar;
   Float_t         weight;
   Float_t         refpvz;
   Float_t         pudensity;
   Float_t         gpudensity;
   Long64_t        npv;
   Long64_t        run;
   Long64_t        lumi;
   Long64_t        evt;
   UChar_t         nref;
   vector<unsigned char> *refrank;
   vector<int>     *refpdgid;
   vector<int>     *refpdgid_algorithmicDef;
   vector<int>     *refpdgid_physicsDef;
   vector<float>   *refe;
   vector<float>   *refpt;
   vector<float>   *refeta;
   vector<float>   *refphi;
   vector<float>   *refy;
   vector<float>   *refdrjt;
   vector<float>   *refarea;
   vector<float>   *jte;
   vector<float>   *jtpt;
   vector<float>   *jteta;
   vector<float>   *jtphi;
   vector<float>   *jty;
   vector<float>   *jtjec;
   vector<float>   *jtarea;
   vector<float>   *jtchf;
   vector<float>   *jtnhf;
   vector<float>   *jtnef;
   vector<float>   *jtcef;
   vector<float>   *jtmuf;
   vector<float>   *jthfhf;
   vector<float>   *jthfef;
   vector<float>   *refdzvtx;

   // List of branches
   TBranch        *b_npus;   //!
   TBranch        *b_tnpus;   //!
   TBranch        *b_zpositions;   //!
   TBranch        *b_bxns;   //!
   TBranch        *b_sumpt_lowpt;   //!
   TBranch        *b_sumpt_highpt;   //!
   TBranch        *b_ntrks_lowpt;   //!
   TBranch        *b_ntrks_highpt;   //!
   TBranch        *b_rhos;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_beta;   //!
   TBranch        *b_betaStar;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_refpvz;   //!
   TBranch        *b_pudensity;   //!
   TBranch        *b_gpudensity;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_nref;   //!
   TBranch        *b_refrank;   //!
   TBranch        *b_refpdgid;   //!
   TBranch        *b_refpdgid_algorithmicDef;   //!
   TBranch        *b_refpdgid_physicsDef;   //!
   TBranch        *b_refe;   //!
   TBranch        *b_refpt;   //!
   TBranch        *b_refeta;   //!
   TBranch        *b_refphi;   //!
   TBranch        *b_refy;   //!
   TBranch        *b_refdrjt;   //!
   TBranch        *b_refarea;   //!
   TBranch        *b_jte;   //!
   TBranch        *b_jtpt;   //!
   TBranch        *b_jteta;   //!
   TBranch        *b_jtphi;   //!
   TBranch        *b_jty;   //!
   TBranch        *b_jtjec;   //!
   TBranch        *b_jtarea;   //!
   TBranch        *b_jtchf;   //!
   TBranch        *b_jtnhf;   //!
   TBranch        *b_jtnef;   //!
   TBranch        *b_jtcef;   //!
   TBranch        *b_jtmuf;   //!
   TBranch        *b_jthfhf;   //!
   TBranch        *b_jthfef;   //!
   TBranch        *b_refdzvtx;   //!

   Example(TTree *tree=0);
   virtual ~Example();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Example_cxx
Example::Example(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("JRAExample.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("JRAExample.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("JRAExample.root:/ak4pf");
      dir->GetObject("t",tree);

   }
   Init(tree);
}

Example::~Example()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Example::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Example::LoadTree(Long64_t entry)
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

void Example::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   npus = 0;
   tnpus = 0;
   zpositions = 0;
   bxns = 0;
   sumpt_lowpt = 0;
   sumpt_highpt = 0;
   ntrks_lowpt = 0;
   ntrks_highpt = 0;
   rhos = 0;
   refrank = 0;
   refpdgid = 0;
   refpdgid_algorithmicDef = 0;
   refpdgid_physicsDef = 0;
   refe = 0;
   refpt = 0;
   refeta = 0;
   refphi = 0;
   refy = 0;
   refdrjt = 0;
   refarea = 0;
   jte = 0;
   jtpt = 0;
   jteta = 0;
   jtphi = 0;
   jty = 0;
   jtjec = 0;
   jtarea = 0;
   jtchf = 0;
   jtnhf = 0;
   jtnef = 0;
   jtcef = 0;
   jtmuf = 0;
   jthfhf = 0;
   jthfef = 0;
   refdzvtx = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("npus", &npus, &b_npus);
   fChain->SetBranchAddress("tnpus", &tnpus, &b_tnpus);
   fChain->SetBranchAddress("zpositions", &zpositions, &b_zpositions);
   fChain->SetBranchAddress("bxns", &bxns, &b_bxns);
   fChain->SetBranchAddress("sumpt_lowpt", &sumpt_lowpt, &b_sumpt_lowpt);
   fChain->SetBranchAddress("sumpt_highpt", &sumpt_highpt, &b_sumpt_highpt);
   fChain->SetBranchAddress("ntrks_lowpt", &ntrks_lowpt, &b_ntrks_lowpt);
   fChain->SetBranchAddress("ntrks_highpt", &ntrks_highpt, &b_ntrks_highpt);
   fChain->SetBranchAddress("rhos", &rhos, &b_rhos);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("beta", &beta, &b_beta);
   fChain->SetBranchAddress("betaStar", &betaStar, &b_betaStar);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("refpvz", &refpvz, &b_refpvz);
   fChain->SetBranchAddress("pudensity", &pudensity, &b_pudensity);
   fChain->SetBranchAddress("gpudensity", &gpudensity, &b_gpudensity);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("nref", &nref, &b_nref);
   fChain->SetBranchAddress("refrank", &refrank, &b_refrank);
   fChain->SetBranchAddress("refpdgid", &refpdgid, &b_refpdgid);
   fChain->SetBranchAddress("refpdgid_algorithmicDef", &refpdgid_algorithmicDef, &b_refpdgid_algorithmicDef);
   fChain->SetBranchAddress("refpdgid_physicsDef", &refpdgid_physicsDef, &b_refpdgid_physicsDef);
   fChain->SetBranchAddress("refe", &refe, &b_refe);
   fChain->SetBranchAddress("refpt", &refpt, &b_refpt);
   fChain->SetBranchAddress("refeta", &refeta, &b_refeta);
   fChain->SetBranchAddress("refphi", &refphi, &b_refphi);
   fChain->SetBranchAddress("refy", &refy, &b_refy);
   fChain->SetBranchAddress("refdrjt", &refdrjt, &b_refdrjt);
   fChain->SetBranchAddress("refarea", &refarea, &b_refarea);
   fChain->SetBranchAddress("jte", &jte, &b_jte);
   fChain->SetBranchAddress("jtpt", &jtpt, &b_jtpt);
   fChain->SetBranchAddress("jteta", &jteta, &b_jteta);
   fChain->SetBranchAddress("jtphi", &jtphi, &b_jtphi);
   fChain->SetBranchAddress("jty", &jty, &b_jty);
   fChain->SetBranchAddress("jtjec", &jtjec, &b_jtjec);
   fChain->SetBranchAddress("jtarea", &jtarea, &b_jtarea);
   fChain->SetBranchAddress("jtchf", &jtchf, &b_jtchf);
   fChain->SetBranchAddress("jtnhf", &jtnhf, &b_jtnhf);
   fChain->SetBranchAddress("jtnef", &jtnef, &b_jtnef);
   fChain->SetBranchAddress("jtcef", &jtcef, &b_jtcef);
   fChain->SetBranchAddress("jtmuf", &jtmuf, &b_jtmuf);
   fChain->SetBranchAddress("jthfhf", &jthfhf, &b_jthfhf);
   fChain->SetBranchAddress("jthfef", &jthfef, &b_jthfef);
   fChain->SetBranchAddress("refdzvtx", &refdzvtx, &b_refdzvtx);
   Notify();
}

Bool_t Example::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Example::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Example::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Example_cxx
