#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"

#include "Code/TauHelperFunctions3.h"

#include "JetEnergyScale.h"

#define PI 3.14159265358979323846264338327950288479716939937510

class StraightTreeMessenger;
class SmearTreeMessenger;
int GetBin(double X, double Edge[], int BinCount);

class StraightTreeMessenger
{
public:
   TTree *Tree;
   bool IsMC, UseMCWeight;
   int SD;
   int Trigger;
public:   // direct quantities
   double JetPT, JetEta, JetPhi, RawJetPT, MatchJetPT;
   double SDRecoDR, SDMass;
   double SDSubJetPT1, SDSubJetPT2;
   double SDSubJetEta1, SDSubJetEta2;
   double SDSubJetPhi1, SDSubJetPhi2;
   double MCWeight, Centrality, PTHat;
   bool PassFilter, PassTrigger;
   double MatchDR;
public:   // derived quantities
   double SDZG;
   double SDMassRatio;
   int SysBin;
   double PTPT;
public:
   StraightTreeMessenger(TFile &File, string TreeName, bool ismc, int sd, int trigger);
   void Initialize();
   void GetEntry(int iE);
   bool PassPTHat(double PTHatMin);
   bool PassPTHat(double PTHatMin, double PTHatMax);
   bool PassSelection();
   int CentralityBin(double CBinEdge[], int BinCount);
   int PTBin(double PTBinEdge[], int BinCount);
   int JetBin(double PTBinEdge[], int BinCount);
   int AngleBin(double AngleBinEdge[], int BinCount);
   int CentralityInt();
};

class SmearTreeMessenger
{
public:
   TTree *Tree;
   bool IsMC, UseMCWeight;
   int SD;
public:   // direct quantities
   double JetPT, JetRawPT, JetEta, JetPhi, OriginalJetPT, OriginalJetEta, OriginalJetPhi;
   double TotalStuffInJet;
   double SDSubJetPT;
   double SDSubJetPT1, SDSubJetPT2;
   double SDSubJetEta1, SDSubJetEta2;
   double SDSubJetPhi1, SDSubJetPhi2;
   double SDRecoDR, SDZG, SDMass;
   double MCWeight, Centrality, PTHat;
   double PTInJet, Rho, TotalPT;
   bool PassFilter, PassTrigger;
public:   // derived quantities
   double MatchDR;
   double SDMassRatio;
   int SysBin;
   double PTPT;
public:
   JetEnergyScale *JES;
public:
   SmearTreeMessenger(TFile &File, string TreeName, bool ismc, int sd);
   void Initialize();
   void GetEntry(int iE);
   bool PassPTHat(double PTHatMin);
   bool PassPTHat(double PTHatMin, double PTHatMax);
   bool PassSelection();
   void SetJES(JetEnergyScale *jes = NULL);
   int CentralityBin(double CBinEdge[], int BinCount);
   int PTBin(double PTBinEdge[], int BinCount);
   int JetBin(double PTBinEdge[], int BinCount);
   int AngleBin(double AngleBinEdge[], int BinCount);
   int CentralityInt();
};





