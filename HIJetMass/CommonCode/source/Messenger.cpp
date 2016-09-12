#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "include/Messenger.h"

namespace EmptyVectors
{
   std::vector<double> EmptyVectorDouble;
   std::vector<float> EmptyVectorFloat;
   std::vector<int> EmptyVectorInt;
   std::vector<std::vector<float> > EmptyVectorVectorFloat;
}

HiEventTreeMessenger::HiEventTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("hiEvtAnalyzer/HiTree");
   Initialize();
}

HiEventTreeMessenger::HiEventTreeMessenger(TTree *HiEventTree)
{
   Initialize(HiEventTree);
}
   
bool HiEventTreeMessenger::Initialize(TTree *HiEventTree)
{
   Tree = HiEventTree;
   return Initialize();
}

bool HiEventTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   if(Tree->GetBranch("hiHF"))  Tree->SetBranchAddress("hiHF", &hiHF);
   else                         hiHF = 0;
   if(Tree->GetBranch("hiBin")) Tree->SetBranchAddress("hiBin", &hiBin);
   else                         hiBin = 0;
   if(Tree->GetBranch("run"))   Tree->SetBranchAddress("run", &run);
   else                         run = 1;
   
   return true;
}

bool HiEventTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

RhoTreeMessenger::RhoTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("hiFJRhoAnalyzer/t");
   Initialize();
}

RhoTreeMessenger::RhoTreeMessenger(TTree *RhoTree)
{
   Initialize(RhoTree);
}
   
bool RhoTreeMessenger::Initialize(TTree *RhoTree)
{
   Tree = RhoTree;
   return Initialize();
}

bool RhoTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   EtaMax = NULL;
   Rho = NULL;
   RhoM = NULL;

   if(Tree->GetBranch("etaMax")) Tree->SetBranchAddress("etaMax", &EtaMax);
   else                          EtaMax = &EmptyVectors::EmptyVectorDouble;
   if(Tree->GetBranch("rho"))    Tree->SetBranchAddress("rho", &Rho);
   else                          Rho = &EmptyVectors::EmptyVectorDouble;
   if(Tree->GetBranch("rhom"))   Tree->SetBranchAddress("rhom", &RhoM);
   else                          RhoM = &EmptyVectors::EmptyVectorDouble;

   return true;
}

bool RhoTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

SkimTreeMessenger::SkimTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("skimanalysis/HltTree");
   Initialize();
}

SkimTreeMessenger::SkimTreeMessenger(TTree *SkimTree)
{
   Initialize(SkimTree);
}

bool SkimTreeMessenger::Initialize(TTree *SkimTree)
{
   Tree = SkimTree;
   return Initialize();
}

bool SkimTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   if(Tree->GetBranch("HBHENoiseFilterResult"))
      Tree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoise);
   else
      HBHENoise = 1;
   if(Tree->GetBranch("HBHENoiseFilterResultRun2Loose"))
      Tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseRun2Loose);
   else
      HBHENoiseRun2Loose = 1;
   if(Tree->GetBranch("pprimaryVertexFilter"))
      Tree->SetBranchAddress("pprimaryVertexFilter", &PVFilter);
   else
      PVFilter = 1;
   if(Tree->GetBranch("pclusterCompatibilityFilter"))
      Tree->SetBranchAddress("pclusterCompatibilityFilter", &ClusterCompatibilityFilter);
   else
      ClusterCompatibilityFilter = 1;
   if(Tree->GetBranch("phfCoincFilter3"))
      Tree->SetBranchAddress("phfCoincFilter3", &HFCoincidenceFilter);
   else
      HFCoincidenceFilter = 1;
   if(Tree->GetBranch("pcollisionEventSelection"))
      Tree->SetBranchAddress("pcollisionEventSelection", &CollisionEventSelection);
   else
      CollisionEventSelection = 1;

   return true;
}

bool SkimTreeMessenger::PassBasicFilter()
{
   if(HBHENoise == 0)
      return false;
   if(HBHENoiseRun2Loose == 0)
      return false;
   if(PVFilter == 0)
      return false;
   if(ClusterCompatibilityFilter == 0)
      return false;
   if(HFCoincidenceFilter == 0)
      return false;
   if(CollisionEventSelection == 0)
      return false;

   return true;
}

bool SkimTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

JetTreeMessenger::JetTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

JetTreeMessenger::JetTreeMessenger(TTree *JetTree)
{
   Initialize(JetTree);
}

bool JetTreeMessenger::Initialize(TTree *JetTree)
{
   Tree = JetTree;
   return Initialize();
}

bool JetTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   JetSubJetPT = NULL;
   JetSubJetEta = NULL;
   JetSubJetPhi = NULL;
   JetSubJetM = NULL;
   RefGSubJetPT = NULL;
   RefGSubJetEta = NULL;
   RefGSubJetPhi = NULL;
   RefGSubJetM = NULL;

   if(Tree->GetBranch("nref"))    Tree->SetBranchAddress("nref", &JetCount);
   else                           JetCount = 0;
   if(Tree->GetBranch("rawpt"))   Tree->SetBranchAddress("rawpt", &JetRawPT);
   if(Tree->GetBranch("jtpt"))    Tree->SetBranchAddress("jtpt", &JetPT);
   if(Tree->GetBranch("jteta"))   Tree->SetBranchAddress("jteta", &JetEta);
   if(Tree->GetBranch("jty"))     Tree->SetBranchAddress("jty", &JetY);
   if(Tree->GetBranch("jtphi"))   Tree->SetBranchAddress("jtphi", &JetPhi);
   if(Tree->GetBranch("jtpu"))    Tree->SetBranchAddress("jtpu", &JetPU);
   if(Tree->GetBranch("jtm"))     Tree->SetBranchAddress("jtm", &JetM);
   if(Tree->GetBranch("jtarea"))  Tree->SetBranchAddress("jtarea", &JetArea);

   if(Tree->GetBranch("jtSubJetPt"))
      Tree->SetBranchAddress("jtSubJetPt", &JetSubJetPT);
   else
      JetSubJetPT = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetEta"))
      Tree->SetBranchAddress("jtSubJetEta", &JetSubJetEta);
   else
      JetSubJetEta = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetPhi"))
      Tree->SetBranchAddress("jtSubJetPhi", &JetSubJetPhi);
   else
      JetSubJetPhi = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetM"))
      Tree->SetBranchAddress("jtSubJetM", &JetSubJetM);
   else
      JetSubJetM = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtsym"))
      Tree->SetBranchAddress("jtsym", &JetSym);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         JetSym[i] = -1;
   if(Tree->GetBranch("jtdroppedBranches"))
      Tree->SetBranchAddress("jtdroppedBranches", &JetDroppedBranches);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         JetDroppedBranches[i] = -1;
   
   if(Tree->GetBranch("refpt"))   Tree->SetBranchAddress("refpt", &RefPT);
   if(Tree->GetBranch("refeta"))  Tree->SetBranchAddress("refeta", &RefEta);
   if(Tree->GetBranch("refy"))    Tree->SetBranchAddress("refy", &RefY);
   if(Tree->GetBranch("refphi"))  Tree->SetBranchAddress("refphi", &RefPhi);
   if(Tree->GetBranch("refm"))    Tree->SetBranchAddress("refm", &RefM);
   if(Tree->GetBranch("refarea")) Tree->SetBranchAddress("refarea", &RefArea);
   
   if(Tree->GetBranch("refptG"))  Tree->SetBranchAddress("refptG", &RefGPT);
   if(Tree->GetBranch("refetaG")) Tree->SetBranchAddress("refetaG", &RefGEta);
   if(Tree->GetBranch("refphiG")) Tree->SetBranchAddress("refphiG", &RefGPhi);
   if(Tree->GetBranch("refmG"))   Tree->SetBranchAddress("refmG", &RefGM);

   if(Tree->GetBranch("refSubJetPt"))
      Tree->SetBranchAddress("refSubJetPt", &RefGSubJetPT);
   else
      RefGSubJetPT = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetEta"))
      Tree->SetBranchAddress("refSubJetEta", &RefGSubJetEta);
   else
      RefGSubJetEta = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetPhi"))
      Tree->SetBranchAddress("refSubJetPhi", &RefGSubJetPhi);
   else
      RefGSubJetPhi = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetM"))
      Tree->SetBranchAddress("refSubJetM", &RefGSubJetM);
   else
      RefGSubJetM = &EmptyVectors::EmptyVectorVectorFloat;
   
   if(Tree->GetBranch("ngen"))    Tree->SetBranchAddress("ngen", &GenCount);
   else                           GenCount = 0;
   
   if(Tree->GetBranch("genmatchindex"))
      Tree->SetBranchAddress("genmatchindex", &GenMatchIndex);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         GenMatchIndex[i] = -1;
   if(Tree->GetBranch("genpt"))   Tree->SetBranchAddress("genpt", &GenPT);
   if(Tree->GetBranch("geneta"))  Tree->SetBranchAddress("geneta", &GenEta);
   if(Tree->GetBranch("geny"))    Tree->SetBranchAddress("geny", &GenY);
   if(Tree->GetBranch("genphi"))  Tree->SetBranchAddress("genphi", &GenPhi);
   if(Tree->GetBranch("genm"))    Tree->SetBranchAddress("genm", &GenM);

   return true;
}

bool JetTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

GenParticleTreeMessenger::GenParticleTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("HiGenParticleAna/hi");
   Initialize();
}

GenParticleTreeMessenger::GenParticleTreeMessenger(TTree *GenParticleTree)
{
   Initialize(GenParticleTree);
}

bool GenParticleTreeMessenger::Initialize(TTree *GenParticleTree)
{
   Tree = GenParticleTree;
   return Initialize();
}

bool GenParticleTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   PT = NULL;
   Eta = NULL;
   Phi = NULL;
   ID = NULL;
   Charge = NULL;
   DaughterCount = NULL;

   if(Tree->GetBranch("npart")) Tree->SetBranchAddress("npart", &NPart);
   else                         NPart = 0;
   if(Tree->GetBranch("ncoll")) Tree->SetBranchAddress("ncoll", &NColl);
   else                         NColl = 0;
   if(Tree->GetBranch("nhard")) Tree->SetBranchAddress("nhard", &NHard);
   else                         NHard = 0;
   if(Tree->GetBranch("phi0"))  Tree->SetBranchAddress("phi0", &Phi0);
   else                         Phi0 = 0;

   if(Tree->GetBranch("pt"))    Tree->SetBranchAddress("pt", &PT);
   else                         PT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("eta"))   Tree->SetBranchAddress("eta", &Eta);
   else                         Eta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("phi"))   Tree->SetBranchAddress("phi", &Phi);
   else                         Phi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pdg"))   Tree->SetBranchAddress("pdg", &ID);
   else                         ID = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("chg")) Tree->SetBranchAddress("chg", &Charge);
   else                         Charge = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("nDaughters")) Tree->SetBranchAddress("nDaughters", &DaughterCount);
   else                         DaughterCount = &EmptyVectors::EmptyVectorInt;

   return true;
}

bool GenParticleTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

PFTreeMessenger::PFTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

PFTreeMessenger::PFTreeMessenger(TTree *PFTree)
{
   Initialize(PFTree);
}

bool PFTreeMessenger::Initialize(TTree *PFTree)
{
   Tree = PFTree;
   return Initialize();
}

bool PFTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   ID = NULL;
   PT = NULL;
   E = NULL;
   Eta = NULL;
   Phi = NULL;

   if(Tree->GetBranch("pfId"))     Tree->SetBranchAddress("pfId", &ID);
   else                            ID = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("pfPt"))     Tree->SetBranchAddress("pfPt", &PT);
   else                            PT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfEnergy")) Tree->SetBranchAddress("pfEnergy", &E);
   else                            E = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfEta"))    Tree->SetBranchAddress("pfEta", &Eta);
   else                            Eta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfPhi"))    Tree->SetBranchAddress("pfPhi", &Phi);
   else                            Phi = &EmptyVectors::EmptyVectorFloat;

   return true;
}

bool PFTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}





