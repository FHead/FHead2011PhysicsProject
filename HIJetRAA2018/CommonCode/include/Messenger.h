#include <iostream>
#include <vector>

#include "TTree.h"
#include "TFile.h"

#define JETCOUNTMAX 200
#define GENCOUNTMAX 100
#define VERTEXCOUNTMAX 200
#define PLANEMAX 200

class HiEventTreeMessenger;
class GGTreeMessenger;
class RhoTreeMessenger;
class SkimTreeMessenger;
class JetTreeMessenger;
class GenParticleTreeMessenger;
class PFTreeMessenger;
class TriggerTreeMessenger;
class TriggerObjectTreeMessenger;
class TrackTreeMessenger;

class HiEventTreeMessenger
{
public:
   TTree *Tree;
   float hiHF;
   int hiBin;
   unsigned int Run;
   unsigned long long Event;
   unsigned int Lumi;
   float weight;
   float hiHFplus;
   float hiHFminus;
   float hiHFplusEta4;
   float hiHFminusEta4;
   int hiNevtPlane;
   float hiEvtPlanes[PLANEMAX];
public:
   HiEventTreeMessenger(TFile &File);
   HiEventTreeMessenger(TFile *File);
   HiEventTreeMessenger(TTree *HiEventTree);
   bool Initialize(TTree *HiEventTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class GGTreeMessenger
{
public:
   TTree *Tree;
   int NPUInfo;
   std::vector<int> *PUCount;
   std::vector<int> *PUBX;
   std::vector<float> *PUTrue;
   int PFJetCount;
   std::vector<float> *PFJetPT;
   std::vector<float> *PFJetEta;
   std::vector<float> *PFJetPhi;
   int CaloJetCount;
   std::vector<float> *CaloJetPT;
   std::vector<float> *CaloJetEta;
   std::vector<float> *CaloJetPhi;
   int GenJetCount;
   std::vector<float> *GenJetPT;
   std::vector<float> *GenJetEta;
   std::vector<float> *GenJetPhi;
public:
   GGTreeMessenger(TFile &File, std::string TreeName = "ggHiNtuplizer/EventTree");
   GGTreeMessenger(TFile *File, std::string TreeName = "ggHiNtuplizer/EventTree");
   GGTreeMessenger(TTree *EventTree);
   bool Initialize(TTree *EventTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class RhoTreeMessenger
{
public:
   TTree *Tree;
   std::vector<double> *EtaMax;
   std::vector<double> *Rho;
   std::vector<double> *RhoM;
public:
   RhoTreeMessenger(TFile &File);
   RhoTreeMessenger(TFile *File);
   RhoTreeMessenger(TTree *RhoTree);
   bool Initialize(TTree *RhoTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class SkimTreeMessenger
{
public:
   TTree *Tree;
   int HBHENoise;
   int HBHENoiseRun2Loose;
   int PVFilter;
   int ClusterCompatibilityFilter;
   int HFCoincidenceFilter;
   int HFCoincidenceFilter2Th4;
   int CollisionEventSelection;
public:
   SkimTreeMessenger(TFile &File);
   SkimTreeMessenger(TFile *File);
   SkimTreeMessenger(TTree *SkimTree);
   bool Initialize(TTree *SkimTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   bool PassBasicFilter();
   bool PassBasicFilterLoose();
};

class JetTreeMessenger
{
public:
   TTree *Tree;
   float PTHat;
   int JetCount;
   float JetRawPT[JETCOUNTMAX];
   float JetPT[JETCOUNTMAX];
   float JetEta[JETCOUNTMAX];
   float JetY[JETCOUNTMAX];
   float JetPhi[JETCOUNTMAX];
   float JetPU[JETCOUNTMAX];
   float JetM[JETCOUNTMAX];
   float JetTau1[JETCOUNTMAX];
   float JetTau2[JETCOUNTMAX];
   float JetTau3[JETCOUNTMAX];
   float JetArea[JETCOUNTMAX];
   float JetCSVV1[JETCOUNTMAX];
   float JetCSVV2[JETCOUNTMAX];
   float JetCSVV1N[JETCOUNTMAX];
   float JetCSVV2N[JETCOUNTMAX];
   float JetCSVV1P[JETCOUNTMAX];
   float JetCSVV2P[JETCOUNTMAX];
   std::vector<std::vector<float> > *JetSubJetPT;
   std::vector<std::vector<float> > *JetSubJetEta;
   std::vector<std::vector<float> > *JetSubJetPhi;
   std::vector<std::vector<float> > *JetSubJetM;
   float JetSym[JETCOUNTMAX];
   int JetDroppedBranches[JETCOUNTMAX];
   float RefPT[JETCOUNTMAX];
   float RefEta[JETCOUNTMAX];
   float RefY[JETCOUNTMAX];
   float RefPhi[JETCOUNTMAX];
   float RefM[JETCOUNTMAX];
   float RefArea[JETCOUNTMAX];
   float RefGPT[JETCOUNTMAX];
   float RefGEta[JETCOUNTMAX];
   float RefGPhi[JETCOUNTMAX];
   float RefGM[JETCOUNTMAX];
   float RefPartonPT[JETCOUNTMAX];
   int RefPartonFlavor[JETCOUNTMAX];
   int RefPartonFlavorForB[JETCOUNTMAX];
   std::vector<std::vector<float> > *RefGSubJetPT;
   std::vector<std::vector<float> > *RefGSubJetEta;
   std::vector<std::vector<float> > *RefGSubJetPhi;
   std::vector<std::vector<float> > *RefGSubJetM;
   int GenCount;
   int GenMatchIndex[JETCOUNTMAX];
   float GenPT[JETCOUNTMAX];
   float GenEta[JETCOUNTMAX];
   float GenY[JETCOUNTMAX];
   float GenPhi[JETCOUNTMAX];
   float GenM[JETCOUNTMAX];
   float HcalSum[JETCOUNTMAX];
   float EcalSum[JETCOUNTMAX];
   float JetPFCHF[JETCOUNTMAX];
   float JetPFNHF[JETCOUNTMAX];
   float JetPFCEF[JETCOUNTMAX];
   float JetPFNEF[JETCOUNTMAX];
   float JetPFMUF[JETCOUNTMAX];
   int JetPFCHM[JETCOUNTMAX];
   int JetPFNHM[JETCOUNTMAX];
   int JetPFCEM[JETCOUNTMAX];
   int JetPFNEM[JETCOUNTMAX];
   int JetPFMUM[JETCOUNTMAX];
public:
   JetTreeMessenger(TFile &File, std::string TreeName = "akCs4PFJetAnalyzer/t");
   JetTreeMessenger(TFile *File, std::string TreeName = "akCs4PFJetAnalyzer/t");
   JetTreeMessenger(TTree *JetTree);
   bool Initialize(TTree *JetTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class GenParticleTreeMessenger
{
public:
   TTree *Tree;
   float NPart;
   float NColl;
   float NHard;
   float Phi0;
   std::vector<float> *PT;
   std::vector<float> *Eta;
   std::vector<float> *Phi;
   std::vector<int> *ID;
   std::vector<int> *Charge;
   std::vector<int> *DaughterCount;
   std::vector<int> *SubEvent;
public:
   GenParticleTreeMessenger(TFile &File);
   GenParticleTreeMessenger(TFile *File);
   GenParticleTreeMessenger(TTree *GenParticleTree);
   bool Initialize(TTree *GenParticleTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class PFTreeMessenger
{
public:
   TTree *Tree;
   std::vector<int> *ID;
   std::vector<float> *PT;
   std::vector<float> *E;
   std::vector<float> *Eta;
   std::vector<float> *Phi;
public:
   PFTreeMessenger(TFile &File, std::string TreeName = "pfcandAnalyzer/pfTree");
   PFTreeMessenger(TFile *File, std::string TreeName = "pfcandAnalyzer/pfTree");
   PFTreeMessenger(TTree *PFTree);
   bool Initialize(TTree *PFTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class TriggerTreeMessenger
{
public:
   TTree *Tree;
   int Run;
   unsigned long long Event;
   int Lumi;
   std::vector<std::string> Name;
   std::vector<int> Decision;
   std::vector<int> Prescale;
   std::vector<bool> Exist;
   std::vector<bool> PrescaleExist;
public:
   TriggerTreeMessenger(TFile &File, std::string TreeName = "hltanalysis/HltTree");
   TriggerTreeMessenger(TFile *File, std::string TreeName = "hltanalysis/HltTree");
   TriggerTreeMessenger(TTree *TriggerTree);
   bool Initialize(TTree *TriggerTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   void FillTriggerNames();
   int FindIndex(std::string Trigger);
   int CheckTrigger(std::string Trigger);
   int CheckTriggerStartWith(std::string Trigger);
   int CheckTrigger(int Index);
   int GetPrescale(std::string Trigger);
   int GetPrescaleStartWith(std::string Trigger);
   int GetPrescale(int Index);
};

class TriggerObjectTreeMessenger
{
public:
   TTree *Tree;
   std::vector<double> *ID;
   std::vector<double> *PT;
   std::vector<double> *Eta;
   std::vector<double> *Phi;
   std::vector<double> *Mass;
public:
   TriggerObjectTreeMessenger(TFile &File, std::string TreeName = "hltobjects/HLT_HIPuAK4CaloJet60_Eta5p1_v");
   TriggerObjectTreeMessenger(TFile *File, std::string TreeName = "hltobjects/HLT_HIPuAK4CaloJet60_Eta5p1_v");
   TriggerObjectTreeMessenger(TTree *TriggerTree);
   bool Initialize(TTree *TriggerTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class TrackTreeMessenger
{
public:
   TTree *Tree;
   int nVtx;
   int nTrkVtx[VERTEXCOUNTMAX];
   float normChi2Vtx[VERTEXCOUNTMAX];
   float sumPtVtx[VERTEXCOUNTMAX];
   float xVtx[VERTEXCOUNTMAX];
   float yVtx[VERTEXCOUNTMAX];
   float zVtx[VERTEXCOUNTMAX];
   float xVtxErr[VERTEXCOUNTMAX];
   float yVtxErr[VERTEXCOUNTMAX];
   float zVtxErr[VERTEXCOUNTMAX];
   float vtxDist2D[VERTEXCOUNTMAX];
   float vtxDist2DErr[VERTEXCOUNTMAX];
   float vtxDist2DSig[VERTEXCOUNTMAX];
   float vtxDist3D[VERTEXCOUNTMAX];
   float vtxDist3DErr[VERTEXCOUNTMAX];
   float vtxDist3DSig[VERTEXCOUNTMAX];
public:
   TrackTreeMessenger(TFile &File, std::string TreeName = "ppTrack/trackTree");
   TrackTreeMessenger(TFile *File, std::string TreeName = "ppTrack/trackTree");
   TrackTreeMessenger(TTree *TrackTree);
   bool Initialize(TTree *TrackTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   int GetBestVertexIndex();
};


