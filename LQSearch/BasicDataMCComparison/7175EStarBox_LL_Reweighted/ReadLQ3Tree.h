#include <string>
#include <vector>
using namespace std;

#include "TTree.h"

struct TreeRecord;

class TreeRecord
{
public:
   double RunNumber;
   double EventNumber;
   double BunchCrossing;
   double LumiSection;
   double Orbit;
   int CaloJetCount;
   int CaloJetCount30;
   int CaloJetCount50;
   int CaloJetCount100;
   int PileUp;
   double CaloJetE[100];
   double CaloJetPT[100];
   double CaloJetEta[100];
   double CaloJetPhi[100];
   double CaloJetCSVTag[100];
   double CaloJetCSVMTag[100];
   double CaloJetTCHPTag[100];
   double CaloJetTCHETag[100];
   int PFJetCount;
   int PFJetCount30;
   int PFJetCount50;
   int PFJetCount100;
   double PFJetE[100];
   double PFJetPT[100];
   double PFJetEta[100];
   double PFJetPhi[100];
   double PFJetCSVTag[100];
   double PFJetCSVMTag[100];
   double PFJetTCHPTag[100];
   double PFJetTCHETag[100];
   int PrimaryVertexCount;
   double PrimaryVertexMaxSumPT;
   double CaloMET[2];
   double PFMET[2];
   int GoodMuonCount;
   int GoodMuonCountTight;
   int GoodMuonCountLoose;
   double Muon1PT;
   double Muon1Eta;
   double Muon1Phi;
   bool Muon1PassTight;
   bool Muon1PassLoose;
   double Muon2PT;
   double Muon2Eta;
   double Muon2Phi;
   bool Muon2PassTight;
   bool Muon2PassLoose;
   double Muon3PT;
   double Muon3Eta;
   double Muon3Phi;
   bool Muon3PassTight;
   bool Muon3PassLoose;
   int GoodElectronCount;
   int GoodElectronCount95;
   int GoodElectronCount90;
   int GoodElectronCount85;
   int GoodElectronCount80;
   double Electron1PT;
   double Electron1Eta;
   double Electron1Phi;
   double Electron2PT;
   double Electron2Eta;
   double Electron2Phi;
   double Electron3PT;
   double Electron3Eta;
   double Electron3Phi;
   double Electron4PT;
   double Electron4Eta;
   double Electron4Phi;
   bool PassHLT;
   bool PassNoiseFilter;
   bool PassCaloJetID;
   bool PassCaloJet60;
   bool PassPFJetID;
   bool PassPFJet60;
public:
   TreeRecord() { Clear(); }
   ~TreeRecord() { Clear(); }
   void Clear();
   void SetBranchAddress(TTree *Tree);
public:
   vector<double> PUWeight;
   void InitializeWeight(string RootFile);
   double GetCurrentWeight();
   double GetWeight(int NPU);
};

void TreeRecord::Clear()
{
   RunNumber = 0;
   EventNumber = 0;
   BunchCrossing = 0;
   LumiSection = 0;
   Orbit = 0;

   CaloJetCount = 0;
   CaloJetCount30 = 0;
   CaloJetCount50 = 0;
   CaloJetCount100 = 0;
   for(int i = 0; i < 50; i++)
   {
      CaloJetE[i] = -10;
      CaloJetPT[i] = -10;
      CaloJetEta[i] = -10;
      CaloJetPhi[i] = -10;
      CaloJetCSVTag[i] = -10;
      CaloJetCSVMTag[i] = -10;
      CaloJetTCHPTag[i] = -10;
      CaloJetTCHETag[i] = -10;
   }

   PFJetCount = 0;
   PFJetCount30 = 0;
   PFJetCount50 = 0;
   PFJetCount100 = 0;
   for(int i = 0; i < 50; i++)
   {
      PFJetE[i] = -10;
      PFJetPT[i] = -10;
      PFJetEta[i] = -10;
      PFJetPhi[i] = -10;
      PFJetCSVTag[i] = -10;
      PFJetCSVMTag[i] = -10;
      PFJetTCHPTag[i] = -10;
      PFJetTCHETag[i] = -10;
   }

   PrimaryVertexCount = 0;
   PrimaryVertexMaxSumPT = 0;

   CaloMET[0] = 0;   CaloMET[1] = 0;
   PFMET[0] = 0;   PFMET[1] = 0;

   GoodMuonCount = 0;
   Muon1PT = 0;
   Muon1Eta = 0;
   Muon1Phi = 0;
   Muon2PT = 0;
   Muon2Eta = 0;
   Muon2Phi = 0;

   GoodElectronCount = 0;

   PassHLT = false;
   PassNoiseFilter = false;
   PassCaloJetID = false;
   PassCaloJet60 = false;
   PassPFJetID = false;
   PassPFJet60 = false;
}

void TreeRecord::SetBranchAddress(TTree *Tree)
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("RunNumber", &RunNumber);
   Tree->SetBranchAddress("EventNumber", &EventNumber);
   Tree->SetBranchAddress("BunchCrossing", &BunchCrossing);
   Tree->SetBranchAddress("LumiSection", &LumiSection);
   Tree->SetBranchAddress("Orbit", &Orbit);
   Tree->SetBranchAddress("PileUp", &PileUp);
   Tree->SetBranchAddress("CaloJetCount", &CaloJetCount);
   Tree->SetBranchAddress("CaloJetCount30", &CaloJetCount30);
   Tree->SetBranchAddress("CaloJetCount50", &CaloJetCount50);
   Tree->SetBranchAddress("CaloJetCount100", &CaloJetCount100);
   Tree->SetBranchAddress("CaloJetE", &CaloJetE);
   Tree->SetBranchAddress("CaloJetPT", CaloJetPT);
   Tree->SetBranchAddress("CaloJetEta", CaloJetEta);
   Tree->SetBranchAddress("CaloJetPhi", CaloJetPhi);
   Tree->SetBranchAddress("CaloJetCSVTag", CaloJetCSVTag);
   Tree->SetBranchAddress("CaloJetCSVMTag", CaloJetCSVMTag);
   Tree->SetBranchAddress("CaloJetTCHPTag", CaloJetTCHPTag);
   Tree->SetBranchAddress("CaloJetTCHETag", CaloJetTCHETag);
   Tree->SetBranchAddress("PFJetCount", &PFJetCount);
   Tree->SetBranchAddress("PFJetCount30", &PFJetCount30);
   Tree->SetBranchAddress("PFJetCount50", &PFJetCount50);
   Tree->SetBranchAddress("PFJetCount100", &PFJetCount100);
   Tree->SetBranchAddress("PFJetE", PFJetE);
   Tree->SetBranchAddress("PFJetPT", PFJetPT);
   Tree->SetBranchAddress("PFJetEta", PFJetEta);
   Tree->SetBranchAddress("PFJetPhi", PFJetPhi);
   Tree->SetBranchAddress("PFJetCSVTag", PFJetCSVTag);
   Tree->SetBranchAddress("PFJetCSVMTag", PFJetCSVMTag);
   Tree->SetBranchAddress("PFJetTCHPTag", PFJetTCHPTag);
   Tree->SetBranchAddress("PFJetTCHETag", PFJetTCHETag);
   Tree->SetBranchAddress("PrimaryVertexCount", &PrimaryVertexCount);
   Tree->SetBranchAddress("PrimaryVertexMaxSumPT", &PrimaryVertexMaxSumPT);
   Tree->SetBranchAddress("CaloMET", CaloMET);
   Tree->SetBranchAddress("PFMET", PFMET);
   Tree->SetBranchAddress("GoodMuonCount", &GoodMuonCount);
   Tree->SetBranchAddress("GoodMuonCountTight", &GoodMuonCountTight);
   Tree->SetBranchAddress("GoodMuonCountLoose", &GoodMuonCountLoose);
   Tree->SetBranchAddress("Muon1PT", &Muon1PT);
   Tree->SetBranchAddress("Muon1Eta", &Muon1Eta);
   Tree->SetBranchAddress("Muon1Phi", &Muon1Phi);
   Tree->SetBranchAddress("Muon1PassTight", &Muon1PassTight);
   Tree->SetBranchAddress("Muon1PassLoose", &Muon1PassLoose);
   Tree->SetBranchAddress("Muon2PT", &Muon2PT);
   Tree->SetBranchAddress("Muon2Eta", &Muon2Eta);
   Tree->SetBranchAddress("Muon2Phi", &Muon2Phi);
   Tree->SetBranchAddress("Muon2PassTight", &Muon2PassTight);
   Tree->SetBranchAddress("Muon2PassLoose", &Muon2PassLoose);
   Tree->SetBranchAddress("Muon3PT", &Muon3PT);
   Tree->SetBranchAddress("Muon3Eta", &Muon3Eta);
   Tree->SetBranchAddress("Muon3Phi", &Muon3Phi);
   Tree->SetBranchAddress("Muon3PassTight", &Muon3PassTight);
   Tree->SetBranchAddress("Muon3PassLoose", &Muon3PassLoose);
   Tree->SetBranchAddress("GoodElectronCount", &GoodElectronCount);
   Tree->SetBranchAddress("GoodElectronCount95", &GoodElectronCount95);
   Tree->SetBranchAddress("GoodElectronCount90", &GoodElectronCount90);
   Tree->SetBranchAddress("GoodElectronCount85", &GoodElectronCount85);
   Tree->SetBranchAddress("GoodElectronCount80", &GoodElectronCount80);
   Tree->SetBranchAddress("Electron1PT", &Electron1PT);
   Tree->SetBranchAddress("Electron1Eta", &Electron1Eta);
   Tree->SetBranchAddress("Electron1Phi", &Electron1Phi);
   Tree->SetBranchAddress("Electron2PT", &Electron2PT);
   Tree->SetBranchAddress("Electron2Eta", &Electron2Eta);
   Tree->SetBranchAddress("Electron2Phi", &Electron2Phi);
   Tree->SetBranchAddress("Electron3PT", &Electron3PT);
   Tree->SetBranchAddress("Electron3Eta", &Electron3Eta);
   Tree->SetBranchAddress("Electron3Phi", &Electron3Phi);
   Tree->SetBranchAddress("Electron4PT", &Electron4PT);
   Tree->SetBranchAddress("Electron4Eta", &Electron4Eta);
   Tree->SetBranchAddress("Electron4Phi", &Electron4Phi);
   Tree->SetBranchAddress("PassHLT", &PassHLT);
   Tree->SetBranchAddress("PassNoiseFilter", &PassNoiseFilter);
   Tree->SetBranchAddress("PassCaloJetID", &PassCaloJetID);
   Tree->SetBranchAddress("PassCaloJet60", &PassCaloJet60);
   Tree->SetBranchAddress("PassPFJetID", &PassPFJetID);
   Tree->SetBranchAddress("PassPFJet60", &PassPFJet60);
}

void TreeRecord::InitializeWeight(string RootFile)
{
    double Flat10[25] = {0.0698146584, 0.0698146584, 0.0698146584,
       0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584, 0.0698146584,
       0.0698146584, 0.0698146584, 0.0698146584, 0.0630151648, 0.0526654164,
       0.0402754482, 0.0292988928, 0.0194384503, 0.0122016783, 0.007207042,
       0.004003637, 0.0020278322, 0.0010739954, 0.0004595759, 0.0002229748,
       0.0001028162, 4.58337152809607E-05};

    double DataAverage[25] = {0};
    TFile F(RootFile.c_str());
    TH1D *H = (TH1D *)F.Get("pileup");
    for(int i = 1; i <= 25; i++)
       DataAverage[i-1] = H->GetBinContent(i);
    F.Close();

    PUWeight.resize(25);
    for(int i = 0; i < 25; i++)
       PUWeight[i] = DataAverage[i] / Flat10[i];

    double Total = 0;
    for(int i = 0; i < 25; i++)
       Total = Total + PUWeight[i];
    for(int i = 0; i < 25; i++)
       PUWeight[i] = PUWeight[i] / Total;
}

double TreeRecord::GetCurrentWeight()
{
   return GetWeight(PileUp);
}

double TreeRecord::GetWeight(int NPU)
{
   if(NPU < PUWeight.size())
      return PUWeight[NPU];
   return 0;
}





