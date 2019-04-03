#include <algorithm>
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
   std::vector<std::vector<int>> EmptyVectorVectorInt;
   std::vector<std::vector<float> > EmptyVectorVectorFloat;
}

HiEventTreeMessenger::HiEventTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("hiEvtAnalyzer/HiTree");
   Initialize();
}

HiEventTreeMessenger::HiEventTreeMessenger(TFile *File)
{
   if(File != NULL)
      Tree = (TTree *)File->Get("hiEvtAnalyzer/HiTree");
   else
      Tree = NULL;
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
   if(Tree->GetBranch("run"))   Tree->SetBranchAddress("run", &Run);
   else                         Run = 1;
   if(Tree->GetBranch("evt"))   Tree->SetBranchAddress("evt", &Event);
   else                         Event = 1;
   if(Tree->GetBranch("lumi"))  Tree->SetBranchAddress("lumi", &Lumi);
   else                         Lumi = 1;
   if(Tree->GetBranch("hiHFplus"))  Tree->SetBranchAddress("hiHFplus", &hiHFplus);
   else                         hiHFplus = 0;
   if(Tree->GetBranch("hiHFminus"))  Tree->SetBranchAddress("hiHFminus", &hiHFminus);
   else                         hiHFminus = 0;
   if(Tree->GetBranch("hiHFplusEta4"))  Tree->SetBranchAddress("hiHFplusEta4", &hiHFplusEta4);
   else                         hiHFplusEta4 = 0;
   if(Tree->GetBranch("hiHFminusEta4"))  Tree->SetBranchAddress("hiHFminusEta4", &hiHFminusEta4);
   else                         hiHFminusEta4 = 0;
   if(Tree->GetBranch("weight"))Tree->SetBranchAddress("weight", &Weight);
   else                         Weight = 1;
   if(Tree->GetBranch("pthat")) Tree->SetBranchAddress("pthat", &PTHat);
   else                         PTHat = 1;
   
   return true;
}

bool HiEventTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

GGTreeMessenger::GGTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

GGTreeMessenger::GGTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
   Initialize();
}

GGTreeMessenger::GGTreeMessenger(TTree *EventTree)
{
   Tree = EventTree;
   Initialize();
}

bool GGTreeMessenger::Initialize(TTree *EventTree)
{
   Tree = EventTree;
   return Initialize();
}

bool GGTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   PUCount = NULL;
   PUBX = NULL;
   PUTrue = NULL;

   if(Tree->GetBranch("nPUInfo"))   Tree->SetBranchAddress("nPUInfo", &NPUInfo);
   else                             NPUInfo = 0;
   if(Tree->GetBranch("nPU"))       Tree->SetBranchAddress("nPU", &PUCount);
   else                             PUCount = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("puBX"))      Tree->SetBranchAddress("puBX", &PUBX);
   else                             PUBX = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("puTrue"))    Tree->SetBranchAddress("puTrue", &PUTrue);
   else                             PUTrue = &EmptyVectors::EmptyVectorFloat;
   
   PFJetPT = NULL;
   PFJetEta = NULL;
   PFJetPhi = NULL;
   CaloJetPT = NULL;
   CaloJetEta = NULL;
   CaloJetPhi = NULL;
   GenJetPT = NULL;
   GenJetEta = NULL;
   GenJetPhi = NULL;

   if(Tree->GetBranch("nPFJt"))         Tree->SetBranchAddress("nPFJt", &PFJetCount);
   else                                 PFJetCount = 0;
   if(Tree->GetBranch("pfJtPt"))        Tree->SetBranchAddress("pfJtPt", &PFJetPT);
   else                                 PFJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfJtEta"))       Tree->SetBranchAddress("pfJtEta", &PFJetEta);
   else                                 PFJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfJtPhi"))       Tree->SetBranchAddress("pfJtPhi", &PFJetPhi);
   else                                 PFJetPhi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("nCaloJt"))       Tree->SetBranchAddress("nCaloJt", &CaloJetCount);
   else                                 CaloJetCount = 0;
   if(Tree->GetBranch("caloJtPt"))      Tree->SetBranchAddress("caloJtPt", &CaloJetPT);
   else                                 CaloJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("caloJtEta"))     Tree->SetBranchAddress("caloJtEta", &CaloJetEta);
   else                                 CaloJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("caloJtPhi"))     Tree->SetBranchAddress("caloJtPhi", &CaloJetPhi);
   else                                 CaloJetPhi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("nGenJt"))        Tree->SetBranchAddress("nGenJt", &GenJetCount);
   else                                 GenJetCount = 0;
   if(Tree->GetBranch("genJtPt"))       Tree->SetBranchAddress("genJtPt", &GenJetPT);
   else                                 GenJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("genJtEta"))      Tree->SetBranchAddress("genJtEta", &GenJetEta);
   else                                 GenJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("genJtPhi"))      Tree->SetBranchAddress("genJtPhi", &GenJetPhi);
   else                                 GenJetPhi = &EmptyVectors::EmptyVectorFloat;

   return true;
}

bool GGTreeMessenger::GetEntry(int iEntry)
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

RhoTreeMessenger::RhoTreeMessenger(TFile *File)
{
   if(File != NULL)
      Tree = (TTree *)File->Get("hiFJRhoAnalyzer/t");
   else
      Tree = NULL;
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

SkimTreeMessenger::SkimTreeMessenger(TFile *File)
{
   if(File != NULL)
      Tree = (TTree *)File->Get("skimanalysis/HltTree");
   else
      Tree = NULL;
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

bool SkimTreeMessenger::PassBasicFilterLoose()
{
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

JetTreeMessenger::JetTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
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

   if(Tree->GetBranch("pthat"))   Tree->SetBranchAddress("pthat", &PTHat);

   if(Tree->GetBranch("nref"))    Tree->SetBranchAddress("nref", &JetCount);
   else                           JetCount = 0;
   if(Tree->GetBranch("rawpt"))   Tree->SetBranchAddress("rawpt", &JetRawPT);
   if(Tree->GetBranch("jtpt"))    Tree->SetBranchAddress("jtpt", &JetPT);
   if(Tree->GetBranch("jteta"))   Tree->SetBranchAddress("jteta", &JetEta);
   if(Tree->GetBranch("jty"))     Tree->SetBranchAddress("jty", &JetY);
   if(Tree->GetBranch("jtphi"))   Tree->SetBranchAddress("jtphi", &JetPhi);
   if(Tree->GetBranch("jtpu"))    Tree->SetBranchAddress("jtpu", &JetPU);
   if(Tree->GetBranch("jtm"))     Tree->SetBranchAddress("jtm", &JetM);
   if(Tree->GetBranch("jttau1"))  Tree->SetBranchAddress("jttau1", &JetTau1);
   if(Tree->GetBranch("jttau2"))  Tree->SetBranchAddress("jttau2", &JetTau2);
   if(Tree->GetBranch("jttau3"))  Tree->SetBranchAddress("jttau3", &JetTau3);
   if(Tree->GetBranch("jtarea"))  Tree->SetBranchAddress("jtarea", &JetArea);
   if(Tree->GetBranch("discr_csvV1"))  Tree->SetBranchAddress("discr_csvV1", &JetCSVV1);
   if(Tree->GetBranch("discr_csvV2"))  Tree->SetBranchAddress("discr_csvV2", &JetCSVV2);
   if(Tree->GetBranch("ndiscr_csvV1")) Tree->SetBranchAddress("ndiscr_csvV1", &JetCSVV1N);
   if(Tree->GetBranch("ndiscr_csvV2")) Tree->SetBranchAddress("ndiscr_csvV2", &JetCSVV2N);
   if(Tree->GetBranch("pdiscr_csvV1")) Tree->SetBranchAddress("pdiscr_csvV1", &JetCSVV1P);
   if(Tree->GetBranch("pdiscr_csvV2")) Tree->SetBranchAddress("pdiscr_csvV2", &JetCSVV2P);

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

   if(Tree->GetBranch("refparton_pt"))
      Tree->SetBranchAddress("refparton_pt", &RefPartonPT);
   if(Tree->GetBranch("refparton_flavor"))
      Tree->SetBranchAddress("refparton_flavor", &RefPartonFlavor);
   if(Tree->GetBranch("refparton_flavorForB"))
      Tree->SetBranchAddress("refparton_flavorForB", &RefPartonFlavorForB);
   
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

   if(Tree->GetBranch("hcalSum")) Tree->SetBranchAddress("hcalSum", &HcalSum);
   if(Tree->GetBranch("ecalSum")) Tree->SetBranchAddress("ecalSum", &EcalSum);

   if(Tree->GetBranch("jtPfCHF")) Tree->SetBranchAddress("jtPfCHF", &JetPFCHF);
   if(Tree->GetBranch("jtPfNHF")) Tree->SetBranchAddress("jtPfNHF", &JetPFNHF);
   if(Tree->GetBranch("jtPfCEF")) Tree->SetBranchAddress("jtPfCEF", &JetPFCEF);
   if(Tree->GetBranch("jtPfNEF")) Tree->SetBranchAddress("jtPfNEF", &JetPFNEF);
   if(Tree->GetBranch("jtPfMUF")) Tree->SetBranchAddress("jtPfMUF", &JetPFMUF);
   if(Tree->GetBranch("jtPfCHM")) Tree->SetBranchAddress("jtPfCHM", &JetPFCHM);
   if(Tree->GetBranch("jtPfNHM")) Tree->SetBranchAddress("jtPfNHM", &JetPFNHM);
   if(Tree->GetBranch("jtPfCEM")) Tree->SetBranchAddress("jtPfCEM", &JetPFCEM);
   if(Tree->GetBranch("jtPfNEM")) Tree->SetBranchAddress("jtPfNEM", &JetPFNEM);
   if(Tree->GetBranch("jtPfMUM")) Tree->SetBranchAddress("jtPfMUM", &JetPFMUM);

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

GenParticleTreeMessenger::GenParticleTreeMessenger(TFile *File)
{
   if(File != NULL)
      Tree = (TTree *)File->Get("HiGenParticleAna/hi");
   else
      Tree = NULL;
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
   DaughterIndex = NULL;
   SubEvent = NULL;

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
   if(Tree->GetBranch("daughterIdx")) Tree->SetBranchAddress("daughterIdx", &DaughterIndex);
   else                         DaughterIndex = &EmptyVectors::EmptyVectorVectorInt;
   if(Tree->GetBranch("sube"))  Tree->SetBranchAddress("sube", &SubEvent);
   else                         SubEvent = &EmptyVectors::EmptyVectorInt;

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

PFTreeMessenger::PFTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
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

TriggerTreeMessenger::TriggerTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TriggerTreeMessenger::TriggerTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
   Initialize();
}

TriggerTreeMessenger::TriggerTreeMessenger(TTree *TriggerTree)
{
   Initialize(TriggerTree);
}

bool TriggerTreeMessenger::Initialize(TTree *TriggerTree)
{
   Tree = TriggerTree;
   return Initialize();
}

bool TriggerTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   if(Tree->GetBranch("Run"))   Tree->SetBranchAddress("Run", &Run);
   else                         Run = 0;
   if(Tree->GetBranch("LumiBlock")) Tree->SetBranchAddress("LumiBlock", &Lumi);
   else                         Lumi = 0;
   if(Tree->GetBranch("Event")) Tree->SetBranchAddress("Event", &Event);
   else                         Event = 0;

   FillTriggerNames();

   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Tree->GetBranch(Name[i].c_str()))
      {
         Tree->SetBranchAddress(Name[i].c_str(), &Decision[i]);
         Exist[i] = true;
         
         if(Tree->GetBranch((Name[i] + "_Prescl").c_str()))
         {
            Tree->SetBranchAddress((Name[i] + "_Prescl").c_str(), &Prescale[i]);
            PrescaleExist[i] = true;
         }
         else
         {
            Prescale[i] = -1;
            PrescaleExist[i] = false;
         }
      }
      else
      {
         Decision[i] = false;
         Exist[i] = false;
      }
   }

   return true;
}

bool TriggerTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}
   
void TriggerTreeMessenger::FillTriggerNames()
{
   Name.clear();
   Decision.clear();
   
   // AA trigger
   Name.push_back("HLT_HIPuAK4CaloJet100_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet80_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet40_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet100Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet80Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet40Eta5p1_v1");

   Name.push_back("HLT_PAAK4PFJet40_Eta5p1v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v2");

   // pp trigger
   Name.push_back("HLT_AK4PFJet80_Eta5p1_v1");

   // L1 pass through
   Name.push_back("HLT_L1SingleJet8_v1_BptxAND_v1");
   Name.push_back("HLT_L1SingleJet12_v1_BptxAND_v1");
   Name.push_back("HLT_L1SingleJet16_v1");
   Name.push_back("HLT_L1SingleJet20_v1");
   Name.push_back("HLT_L1SingleJet35_v1");
   Name.push_back("HLT_L1SingleJet40_v1");
   Name.push_back("HLT_L1SingleJet44_v1");
   Name.push_back("HLT_L1SingleJet60_v1");

   // pA temporary triggers - v16
   // Name.push_back("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1");   // same in v18
   // Name.push_back("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1");   // same in v18
   Name.push_back("HLT_PAAK4PFJetCSV60_Eta2p1_v2");

   // pA temporary triggers - v22
   Name.push_back("HLT_PAAK4CaloJet60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloJet80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloJet100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV100_Eta2p1_v1");

   // pA temporary triggers - v24
   Name.push_back("HLT_L1ZeroBias_BptxAND_v1");
   
   // pA temporary triggers - v27
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV40_Eta2p1_v1");
   
   // pA temporary triggers - v31 / JCv1
   Name.push_back("HLT_PAAK4CaloBJetCSV40_CommonTracking_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV60_CommonTracking_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV80_CommonTracking_Eta2p1_v1");

   // Chris V14
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve40_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve60_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve80_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve40_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve60_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve80_Eta5p1_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton30_Eta3p1_v2");
   Name.push_back("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2");

   Name.push_back("L1_SingleJet12_BptxAND");
   Name.push_back("L1_SingleJet28_BptxAND");
   Name.push_back("L1_SingleJet44_BptxAND");
   Name.push_back("L1_SingleJet56_BptxAND");
   Name.push_back("L1_SingleJet60_BptxAND");
   
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet100_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet100_Eta5p1_v1");

   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND_Initial");
   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND_Final");
   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v1");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v2");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v3");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v4");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v5");

   Name.push_back("L1_SingleJet12_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_BptxAND_Final");
   Name.push_back("L1_SingleJet16_BptxAND_Initial");
   Name.push_back("L1_SingleJet16_BptxAND_Final");
   Name.push_back("L1_SingleJet24_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_BptxAND_Final");
   Name.push_back("L1_SingleJet36_BptxAND_Initial");
   Name.push_back("L1_SingleJet36_BptxAND_Final");
   Name.push_back("L1_SingleJet52_BptxAND_Initial");
   Name.push_back("L1_SingleJet52_BptxAND_Final");
   
   Name.push_back("L1_SingleJet12_ForEta1p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_ForEta1p5_BptxAND_Final");
   Name.push_back("L1_SingleJet12_ForEta2p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_ForEta2p5_BptxAND_Final");
   Name.push_back("L1_SingleJet24_ForEta1p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_ForEta1p5_BptxAND_Final");
   Name.push_back("L1_SingleJet24_ForEta2p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_ForEta2p5_BptxAND_Final");

   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v4");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve40_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve60_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve80_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve40_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve60_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve80_Eta5p1_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton30_Eta3p1_v3");
   Name.push_back("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v3");

   // PP Reference Runs - v4
   Name.push_back("HLT_AK4PFJet30_v15");
   Name.push_back("HLT_AK4PFJet50_v15");
   Name.push_back("HLT_AK4PFJet80_v15");
   Name.push_back("HLT_AK4PFJet100_v15");
   Name.push_back("HLT_AK4PFJet120_v14");

   Name.push_back("HLT_AK4CaloJet30_v10");
   Name.push_back("HLT_AK4CaloJet40_v9");
   Name.push_back("HLT_AK4CaloJet50_v9");
   Name.push_back("HLT_AK4CaloJet80_v9");
   Name.push_back("HLT_AK4CaloJet100_v9");
   Name.push_back("HLT_AK4CaloJet120_v8");

   Name.push_back("HLT_L1SingleJet16_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet20_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet28_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet40_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet60_Eta5p1_v1");

   // pp reference runs - v6
   Name.push_back("HLT_L1SingleJet20FWD");
   Name.push_back("HLT_L1SingleJet35FWD");
   Name.push_back("HLT_L1SingleJet40FWD");
   Name.push_back("HLT_L1SingleJet50FWD");
   Name.push_back("HLT_L1SingleJet60FWD");
   
   Name.push_back("HLT_AK4PFJet30FWD_v14");
   Name.push_back("HLT_AK4PFJet50FWD_v14");
   Name.push_back("HLT_AK4PFJet60FWD_v14");
   Name.push_back("HLT_AK4PFJet70FWD_v14");
   Name.push_back("HLT_AK4PFJet80FWD_v14");

   std::sort(Name.begin(), Name.end());
   std::vector<std::string>::iterator iter = std::unique(Name.begin(), Name.end());
   Name.erase(iter, Name.end());
   Decision.resize(Name.size());
   Prescale.resize(Name.size());
   Exist.resize(Name.size());
   PrescaleExist.resize(Name.size());
}

int TriggerTreeMessenger::FindIndex(std::string Trigger)
{
   std::vector<std::string>::iterator iter
      = std::lower_bound(Name.begin(), Name.end(), Trigger);

   if(iter == Name.end())
      return -1;
   if(Trigger == *iter)
      return (iter - Name.begin());
   return -1;
}

int TriggerTreeMessenger::CheckTrigger(std::string Trigger)
{
   return CheckTrigger(FindIndex(Trigger));
}
   
int TriggerTreeMessenger::CheckTriggerStartWith(std::string Trigger)
{
   bool Found = false;
   int Result = 0;

   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Exist[i] == false || Name[i].find(Trigger) != 0)
         continue;

      Found = true;
      Result = Result + CheckTrigger(i);
   }

   if(Found == true)
      return Result;
   return -1;
}
   
int TriggerTreeMessenger::CheckTrigger(int Index)
{
   if(Index < 0 || Index >= (int)Name.size())
      return -1;
   if(Exist[Index] == false)
      return -1;

   return Decision[Index];
}

int TriggerTreeMessenger::GetPrescale(std::string Trigger)
{
   return GetPrescale(FindIndex(Trigger));
}
   
int TriggerTreeMessenger::GetPrescaleStartWith(std::string Trigger)
{
   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Exist[i] == false || Name[i].find(Trigger) != 0)
         continue;
      return GetPrescale(i);
   }

   return -1;
}

int TriggerTreeMessenger::GetPrescale(int Index)
{
   if(Index < 0 || Index >= (int)Name.size())
      return -1;
   if(Exist[Index] == false)
      return -1;
   if(PrescaleExist[Index] == false)
      return 1;

   return Prescale[Index];
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
   Initialize();
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TTree *TriggerTree)
{
   Initialize(TriggerTree);
}

bool TriggerObjectTreeMessenger::Initialize(TTree *TriggerTree)
{
   Tree = TriggerTree;
   return Initialize();
}

bool TriggerObjectTreeMessenger::Initialize()
{
   ID = NULL;
   PT = NULL;
   Eta = NULL;
   Phi = NULL;
   Mass = NULL;

   if(Tree == NULL)
      return false;

   Tree->SetBranchAddress("TriggerObjID", &ID);
   Tree->SetBranchAddress("pt", &PT);
   Tree->SetBranchAddress("eta", &Eta);
   Tree->SetBranchAddress("phi", &Phi);
   Tree->SetBranchAddress("mass", &Mass);

   return true;
}

bool TriggerObjectTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);

   return true;
}

TrackTreeMessenger::TrackTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TrackTreeMessenger::TrackTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != NULL)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = NULL;
   Initialize();
}

TrackTreeMessenger::TrackTreeMessenger(TTree *TrackTree)
{
   Initialize(TrackTree);
}

bool TrackTreeMessenger::Initialize(TTree *TrackTree)
{
   Tree = TrackTree;
   return Initialize();
}

bool TrackTreeMessenger::Initialize()
{
   if(Tree == NULL)
      return false;

   if(Tree->GetBranch("nTrk"))         Tree->SetBranchAddress("nTrk", &TrackCount);
   else                                TrackCount = 0;

   if(Tree->GetBranch("trkPt"))        Tree->SetBranchAddress("trkPt", &TrackPT);
   if(Tree->GetBranch("trkEta"))       Tree->SetBranchAddress("trkEta", &TrackEta);
   if(Tree->GetBranch("trkPhi"))       Tree->SetBranchAddress("trkPhi", &TrackPhi);
   if(Tree->GetBranch("highPurity"))   Tree->SetBranchAddress("highPurity", &HighPurity);
   if(Tree->GetBranch("trkMVA"))       Tree->SetBranchAddress("trkMVA", &TrackMVA);
   if(Tree->GetBranch("trkAlgo"))      Tree->SetBranchAddress("trkAlgo", &TrackAlgo);

   return true;
}

bool TrackTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == NULL)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}
   










