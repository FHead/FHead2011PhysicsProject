#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"

#include "L1AnalysisCSCTFDataFormat.h"
#include "L1AnalysisL1MenuDataFormat.h"
#include "L1AnalysisCaloTPDataFormat.h"
#include "L1AnalysisRCTDataFormat.h"
#include "L1AnalysisDTTFDataFormat.h"
#include "L1AnalysisRecoClusterDataFormat.h"
#include "L1AnalysisEventDataFormat.h"
#include "L1AnalysisRecoJetDataFormat.h"
#include "L1AnalysisGCTDataFormat.h"
#include "L1AnalysisRecoMetDataFormat.h"
#include "L1AnalysisGMTDataFormat.h"
#include "L1AnalysisRecoMuonDataFormat.h"
#include "L1AnalysisGTDataFormat.h"
#include "L1AnalysisRecoTrackDataFormat.h"
#include "L1AnalysisGeneratorDataFormat.h"
#include "L1AnalysisRecoVertexDataFormat.h"
#include "L1AnalysisL1ExtraDataFormat.h"
#include "L1AnalysisSimulationDataFormat.h"
#include "L1AnalysisL1ExtraUpgradeDataFormat.h"

class L1NTupleMessenger;
class L1MenuTreeMessenger;
class L1ExtraTreeMessenger;
class L1EmulatorMessenger;
class L1EmulatorExtraMessenger;
class L1ExtraUpgradeTreeMessenger;
class GenericObject;

class L1NTupleMessenger
{
public:
   TTree *Tree;
public:
   L1Analysis::L1AnalysisEventDataFormat *Event;
   L1Analysis::L1AnalysisGCTDataFormat *GCT;
   L1Analysis::L1AnalysisGeneratorDataFormat *Generator;
   L1Analysis::L1AnalysisSimulationDataFormat *Simulation;
   L1Analysis::L1AnalysisGMTDataFormat *GMT;
   L1Analysis::L1AnalysisGTDataFormat *GT;
   L1Analysis::L1AnalysisRCTDataFormat *RCT;
   L1Analysis::L1AnalysisDTTFDataFormat *DTTF;
   L1Analysis::L1AnalysisCaloTPDataFormat *CALO;
public:
   // Derived stuff
   vector<FourVector> GenP;
   vector<int> GenID;
   vector<int> GenStatus;
public:
   L1NTupleMessenger(TFile &File, string TreeName = "L1NtupleProducer/L1Tree");
   ~L1NTupleMessenger();
   void SetBranchAddress();
   bool GetEntry(int Entry);
};

class L1MenuTreeMessenger
{
};

class L1ExtraTreeMessenger
{
};

class L1EmulatorMessenger
{
};

class L1EmulatorExtraMessenger
{
};

class L1ExtraUpgradeTreeMessenger
{
public:
   TTree *Tree;
public:
   L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat *L1ExtraUpgrade;
public:
   vector<GenericObject> EG;
   vector<GenericObject> IsoEG;
   vector<GenericObject> TkEG;
   vector<GenericObject> TkEG2;
   vector<GenericObject> TkIsoEG;
   vector<GenericObject> TkEM;
   vector<GenericObject> Tau;
   vector<GenericObject> IsoTau;
   vector<GenericObject> TkTau;
   vector<GenericObject> Jet;
   vector<GenericObject> TkJet;
   vector<GenericObject> FwdJet;
   vector<GenericObject> Muon;
   vector<GenericObject> TkMuon;
   vector<GenericObject> MET;
   vector<GenericObject> TkMET;
   vector<GenericObject> MHT;
   vector<GenericObject> TkMHT;
public:
   L1ExtraUpgradeTreeMessenger(TFile &File, string TreeName = "L1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");
   ~L1ExtraUpgradeTreeMessenger();
   void SetBranchAddress();
   bool GetEntry(int Entry);
   void FillObject(vector<GenericObject> &V, int N,
      vector<double> *ET, vector<double> *Eta, vector<double> *Phi, vector<int> *Bx,
      vector<double> *Iso, vector<double> *VZ, vector<double> *PET);
   void FillObject(vector<GenericObject> &V, int N,
      vector<double> *ET, vector<double> *Eta, vector<double> *Phi, vector<double> *Bx,
      vector<double> *Iso, vector<double> *VZ, vector<double> *PET);
};

class GenericObject
{
public:
   FourVector P;
   int Bx;
   double Iso;
   double VZ;
   double PET;
   int ID;
};





