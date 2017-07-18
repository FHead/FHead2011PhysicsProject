#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"

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
   double JetPT, JetEta, JetPhi, RawJetPT;
   double SDRecoDR, SDSubJetPT1, SDSubJetPT2, SDMass;
   double MCWeight, Centrality, PTHat;
   bool PassFilter, PassTrigger;
   double MatchDR;
public:   // derived quantities
   double SDZG;
   double SDMassRatio;
   int SysBin;
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
   int CentralityInt();
};

class SmearTreeMessenger
{
public:
   TTree *Tree;
   bool IsMC, UseMCWeight;
   int SD;
   TGraph *GMBRMS;
   TGraph *GSmearRMS;
public:   // direct quantities
   double JetPT, JetEta, JetPhi, OriginalJetPT, OriginalJetEta, OriginalJetPhi;
   double SDRecoDR, SDZG, SDMass;
   double MCWeight, Centrality, PTHat;
   double PTInJet, Rho, TotalPT;
   bool PassFilter, PassTrigger;
public:   // derived quantities
   double MatchDR;
   double RawJetPT;
   double SDMassRatio;
   int SysBin;
public:
   SmearTreeMessenger(TFile &File, string TreeName, bool ismc, int sd);
   void Initialize();
   void GetEntry(int iE);
   void SetMB(TGraph *G);
   void SetSmear(TGraph *G);
   bool PassPTHat(double PTHatMin);
   bool PassPTHat(double PTHatMin, double PTHatMax);
   bool PassSelection();
   int CentralityBin(double CBinEdge[], int BinCount);
   int PTBin(double PTBinEdge[], int BinCount);
   int JetBin(double PTBinEdge[], int BinCount);
   double SmearWeight();
   int CentralityInt();
};





