#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

class TreeRecord
{
public:
   double        RunNumber;
   double        EventNumber;
   double        BunchCrossing;
   double        LumiSection;
   double        Orbit;
   int           PileUp;
   int           CaloJetCount;
   int           CaloJetCount30;
   int           CaloJetCount50;
   int           CaloJetCount100;
   double        CaloJetE[100];
   double        CaloJetPT[100];
   double        CaloJetEta[100];
   double        CaloJetPhi[100];
   double        CaloJetCSVTag[100];
   double        CaloJetCSVMTag[100];
   double        CaloJetSSVHETag[100];
   double        CaloJetSSVHPTag[100];
   double        CaloJetTCHPTag[100];
   double        CaloJetTCHETag[100];
   int           PFJetCount;
   int           PFJetCount30;
   int           PFJetCount50;
   int           PFJetCount100;
   double        PFJetE[100];
   double        PFJetPT[100];
   double        PFJetEta[100];
   double        PFJetPhi[100];
   double        PFJetCSVTag[100];
   double        PFJetCSVMTag[100];
   double        PFJetSSVHETag[100];
   double        PFJetSSVHPTag[100];
   double        PFJetTCHPTag[100];
   double        PFJetTCHETag[100];
   int           PrimaryVertexCount;
   double        PrimaryVertexMaxSumPT;
   double        CaloMET[2];
   double        PFMET[2];
   int           GoodMuonCount;
   int           GoodMuonCountTight;
   int           GoodMuonCountLoose;
   double        Muon1PT;
   double        Muon1Eta;
   double        Muon1Phi;
   bool          Muon1PassTight;
   bool          Muon1PassLoose;
   float         Muon1Isolation;
   double        Muon2PT;
   double        Muon2Eta;
   double        Muon2Phi;
   bool          Muon2PassTight;
   bool          Muon2PassLoose;
   float         Muon2Isolation;
   double        Muon3PT;
   double        Muon3Eta;
   double        Muon3Phi;
   bool          Muon3PassTight;
   bool          Muon3PassLoose;
   float         Muon3Isolation;
   double        Muon4PT;
   double        Muon4Eta;
   double        Muon4Phi;
   bool          Muon4PassTight;
   bool          Muon4PassLoose;
   float         Muon4Isolation;
   double        Muon5PT;
   double        Muon5Eta;
   double        Muon5Phi;
   bool          Muon5PassTight;
   bool          Muon5PassLoose;
   float         Muon5Isolation;
   double        Muon6PT;
   double        Muon6Eta;
   double        Muon6Phi;
   bool          Muon6PassTight;
   bool          Muon6PassLoose;
   float         Muon6Isolation;
   double        Muon7PT;
   double        Muon7Eta;
   double        Muon7Phi;
   bool          Muon7PassTight;
   bool          Muon7PassLoose;
   float         Muon7Isolation;
   double        Muon8PT;
   double        Muon8Eta;
   double        Muon8Phi;
   bool          Muon8PassTight;
   bool          Muon8PassLoose;
   float         Muon8Isolation;
   double        Muon9PT;
   double        Muon9Eta;
   double        Muon9Phi;
   bool          Muon9PassTight;
   bool          Muon9PassLoose;
   float         Muon9Isolation;
   double        Muon10PT;
   double        Muon10Eta;
   double        Muon10Phi;
   bool          Muon10PassTight;
   bool          Muon10PassLoose;
   float         Muon10Isolation;
   int           GoodElectronCount;
   int           GoodElectronCount80;
   int           GoodElectronCount85;
   int           GoodElectronCount90;
   int           GoodElectronCount95;
   double        ElectronPT[10];
   double        ElectronEta[10];
   double        ElectronPhi[10];
   bool          ElectronPass95[10];
   bool          ElectronPass90[10];
   bool          ElectronPass85[10];
   bool          ElectronPass80[10];
   double        ElectronIsolation[10];
   int           AllElectronCount;
   double        AllElectronPT[10];
   double        AllElectronEta[10];
   double        AllElectronPhi[10];
   bool          AllElectronPass95[10];
   bool          AllElectronPass90[10];
   bool          AllElectronPass85[10];
   bool          AllElectronPass80[10];
   double        AllElectronIsolation[10];
   double        AllElectronConversionDistance[10];
   double        AllElectronConversionDeltaCotTheta[10];
   double        AllElectronSigmaIEtaIEta[10];
   bool          PassHLT;
   bool          PassNoiseFilter;
   bool          PassCaloJetID;
   bool          PassCaloJet60;
   bool          PassPFJetID;
   bool          PassPFJet60;
   bool          PassDiJetAve30;
   bool          PassDiJetAve60;
   bool          PassDiJetAve80;
   bool          PassDiJetAve110;
   bool          PassDiJetAve150;
   bool          PassDiJetAve190;
   bool          PassDiJetAve240;
   bool          PassDiJetAve300;
   bool          PassDiJetAve370;
   bool          PassDiJetAve15U;
   bool          PassDiJetAve30U;
   bool          PassDiJetAve50U;
   bool          PassDiJetAve70U;
   bool          PassDiJetAve100U;
   bool          PassDiJetAve140U;
   bool          PassDiJetAve180U;
   bool          PassDiJetAve300U;
   bool          PassSingleMu3;
   bool          PassSingleMu5;
   bool          PassSingleMu8;
   bool          PassSingleMu12;
   bool          PassSingleMu15;
   bool          PassSingleMu20;
   bool          PassSingleMu24;
   bool          PassSingleMu30;
   bool          PassSingleMu40;
   bool          PassSingleMu100;
   bool          PassR020MR500;
   bool          PassR020MR550;
   bool          PassR023MR550;
   bool          PassR025MR400;
   bool          PassR025MR450;
   bool          PassR029MR450;
   bool          PassR033MR300;
   bool          PassR033MR350;
   bool          PassR036MR350;
   bool          PassR038MR200;
   bool          PassR038MR250;
   bool          PassR042MR250;
   bool          PassEleL10R020MR200;
   bool          PassEleL10R025MR200;
   bool          PassEleL10R029MR200;
   bool          PassEleT10R020MR200;
   bool          PassMu8R020MR200;
   bool          PassMu8R025MR200;
   bool          PassMu8R029MR200;
   bool          PassMu17Mu8;
   bool          PassMu13Mu8;
   bool          PassMu8EleL17;
   bool          PassMu17EleL8;
public:
   TreeRecord() { Clear(); }
   ~TreeRecord() { Clear(); }
   void Clear();
   void SetBranchAddress(TTree *Tree);
   void Branch(TTree *Tree);
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
   PileUp = 0;
   CaloJetCount = 0;
   CaloJetCount30 = 0;
   CaloJetCount50 = 0;
   CaloJetCount100 = 0;

   for(int i = 0; i < 100; i++)
   {
      CaloJetE[i] = 0;
      CaloJetPT[i] = 0;
      CaloJetEta[i] = 0;
      CaloJetPhi[i] = 0;
      CaloJetCSVTag[i] = 0;
      CaloJetCSVMTag[i] = 0;
      CaloJetSSVHETag[i] = 0;
      CaloJetSSVHPTag[i] = 0;
      CaloJetTCHPTag[i] = 0;
      CaloJetTCHETag[i] = 0;
   }

   PFJetCount = 0;
   PFJetCount30 = 0;
   PFJetCount50 = 0;
   PFJetCount100 = 0;

   for(int i = 0; i < 100; i++)
   {
      PFJetE[i] = 0;
      PFJetPT[i] = 0;
      PFJetEta[i] = 0;
      PFJetPhi[i] = 0;
      PFJetCSVTag[i] = 0;
      PFJetCSVMTag[i] = 0;
      PFJetSSVHETag[i] = 0;
      PFJetSSVHPTag[i] = 0;
      PFJetTCHPTag[i] = 0;
      PFJetTCHETag[i] = 0;
   }

   PrimaryVertexCount = 0;
   PrimaryVertexMaxSumPT = 0;
   CaloMET[0] = 0;
   CaloMET[1] = 0;
   PFMET[0] = 0;
   PFMET[1] = 0;
   GoodMuonCount = 0;
   GoodMuonCountTight = 0;
   GoodMuonCountLoose = 0;
   Muon1PT = 0;
   Muon1Eta = 0;
   Muon1Phi = 0;
   Muon1PassTight = 0;
   Muon1PassLoose = 0;
   Muon1Isolation = 0;
   Muon2PT = 0;
   Muon2Eta = 0;
   Muon2Phi = 0;
   Muon2PassTight = 0;
   Muon2PassLoose = 0;
   Muon2Isolation = 0;
   Muon3PT = 0;
   Muon3Eta = 0;
   Muon3Phi = 0;
   Muon3PassTight = 0;
   Muon3PassLoose = 0;
   Muon3Isolation = 0;
   Muon4PT = 0;
   Muon4Eta = 0;
   Muon4Phi = 0;
   Muon4PassTight = 0;
   Muon4PassLoose = 0;
   Muon4Isolation = 0;
   Muon5PT = 0;
   Muon5Eta = 0;
   Muon5Phi = 0;
   Muon5PassTight = 0;
   Muon5PassLoose = 0;
   Muon5Isolation = 0;
   Muon6PT = 0;
   Muon6Eta = 0;
   Muon6Phi = 0;
   Muon6PassTight = 0;
   Muon6PassLoose = 0;
   Muon6Isolation = 0;
   Muon7PT = 0;
   Muon7Eta = 0;
   Muon7Phi = 0;
   Muon7PassTight = 0;
   Muon7PassLoose = 0;
   Muon7Isolation = 0;
   Muon8PT = 0;
   Muon8Eta = 0;
   Muon8Phi = 0;
   Muon8PassTight = 0;
   Muon8PassLoose = 0;
   Muon8Isolation = 0;
   Muon9PT = 0;
   Muon9Eta = 0;
   Muon9Phi = 0;
   Muon9PassTight = 0;
   Muon9PassLoose = 0;
   Muon9Isolation = 0;
   Muon10PT = 0;
   Muon10Eta = 0;
   Muon10Phi = 0;
   Muon10PassTight = 0;
   Muon10PassLoose = 0;
   Muon10Isolation = 0;
   GoodElectronCount = 0;
   GoodElectronCount80 = 0;
   GoodElectronCount85 = 0;
   GoodElectronCount90 = 0;
   GoodElectronCount95 = 0;
   for(int i = 0; i < 10; i++)
   {
      ElectronPT[i] = 0;
      ElectronEta[i] = 0;
      ElectronPhi[i] = 0;
      ElectronPass95[i] = 0;
      ElectronPass90[i] = 0;
      ElectronPass85[i] = 0;
      ElectronPass80[i] = 0;
      ElectronIsolation[i] = 0;
   }
   
   AllElectronCount = 0;
   for(int i = 0; i < 10; i++)
   {
      AllElectronPT[i] = 0;
      AllElectronEta[i] = 0;
      AllElectronPhi[i] = 0;
      AllElectronPass95[i] = 0;
      AllElectronPass90[i] = 0;
      AllElectronPass85[i] = 0;
      AllElectronPass80[i] = 0;
      AllElectronIsolation[i] = 0;
      AllElectronConversionDistance[i] = 0;
      AllElectronConversionDeltaCotTheta[i] = 0;
      AllElectronSigmaIEtaIEta[i] = 0;
   }
   PassHLT = 0;
   PassNoiseFilter = 0;
   PassCaloJetID = 0;
   PassCaloJet60 = 0;
   PassPFJetID = 0;
   PassPFJet60 = 0;
   PassDiJetAve30 = 0;
   PassDiJetAve60 = 0;
   PassDiJetAve80 = 0;
   PassDiJetAve110 = 0;
   PassDiJetAve150 = 0;
   PassDiJetAve190 = 0;
   PassDiJetAve240 = 0;
   PassDiJetAve300 = 0;
   PassDiJetAve370 = 0;
   PassDiJetAve15U = 0;
   PassDiJetAve30U = 0;
   PassDiJetAve50U = 0;
   PassDiJetAve70U = 0;
   PassDiJetAve100U = 0;
   PassDiJetAve140U = 0;
   PassDiJetAve180U = 0;
   PassDiJetAve300U = 0;
   PassSingleMu3 = 0;
   PassSingleMu5 = 0;
   PassSingleMu8 = 0;
   PassSingleMu12 = 0;
   PassSingleMu15 = 0;
   PassSingleMu20 = 0;
   PassSingleMu24 = 0;
   PassSingleMu30 = 0;
   PassSingleMu40 = 0;
   PassSingleMu100 = 0;
   PassR020MR500 = 0;
   PassR020MR550 = 0;
   PassR023MR550 = 0;
   PassR025MR400 = 0;
   PassR025MR450 = 0;
   PassR029MR450 = 0;
   PassR033MR300 = 0;
   PassR033MR350 = 0;
   PassR036MR350 = 0;
   PassR038MR200 = 0;
   PassR038MR250 = 0;
   PassR042MR250 = 0;
   PassEleL10R020MR200 = 0;
   PassEleL10R025MR200 = 0;
   PassEleL10R029MR200 = 0;
   PassEleT10R020MR200 = 0;
   PassMu8R020MR200 = 0;
   PassMu8R025MR200 = 0;
   PassMu8R029MR200 = 0;
   PassMu17Mu8 = 0;
   PassMu13Mu8 = 0;
   PassMu8EleL17 = 0;
   PassMu17EleL8 = 0;
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
   Tree->SetBranchAddress("CaloJetE", CaloJetE);
   Tree->SetBranchAddress("CaloJetPT", CaloJetPT);
   Tree->SetBranchAddress("CaloJetEta", CaloJetEta);
   Tree->SetBranchAddress("CaloJetPhi", CaloJetPhi);
   Tree->SetBranchAddress("CaloJetCSVTag", CaloJetCSVTag);
   Tree->SetBranchAddress("CaloJetCSVMTag", CaloJetCSVMTag);
   Tree->SetBranchAddress("CaloJetSSVHETag", CaloJetSSVHETag);
   Tree->SetBranchAddress("CaloJetSSVHPTag", CaloJetSSVHPTag);
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
   Tree->SetBranchAddress("PFJetSSVHETag", PFJetSSVHETag);
   Tree->SetBranchAddress("PFJetSSVHPMTag", PFJetSSVHPTag);
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
   Tree->SetBranchAddress("Muon1Isolation", &Muon1Isolation);
   Tree->SetBranchAddress("Muon2PT", &Muon2PT);
   Tree->SetBranchAddress("Muon2Eta", &Muon2Eta);
   Tree->SetBranchAddress("Muon2Phi", &Muon2Phi);
   Tree->SetBranchAddress("Muon2PassTight", &Muon2PassTight);
   Tree->SetBranchAddress("Muon2PassLoose", &Muon2PassLoose);
   Tree->SetBranchAddress("Muon2Isolation", &Muon2Isolation);
   Tree->SetBranchAddress("Muon3PT", &Muon3PT);
   Tree->SetBranchAddress("Muon3Eta", &Muon3Eta);
   Tree->SetBranchAddress("Muon3Phi", &Muon3Phi);
   Tree->SetBranchAddress("Muon3PassTight", &Muon3PassTight);
   Tree->SetBranchAddress("Muon3PassLoose", &Muon3PassLoose);
   Tree->SetBranchAddress("Muon3Isolation", &Muon3Isolation);
   Tree->SetBranchAddress("Muon4PT", &Muon4PT);
   Tree->SetBranchAddress("Muon4Eta", &Muon4Eta);
   Tree->SetBranchAddress("Muon4Phi", &Muon4Phi);
   Tree->SetBranchAddress("Muon4PassTight", &Muon4PassTight);
   Tree->SetBranchAddress("Muon4PassLoose", &Muon4PassLoose);
   Tree->SetBranchAddress("Muon4Isolation", &Muon4Isolation);
   Tree->SetBranchAddress("Muon5PT", &Muon5PT);
   Tree->SetBranchAddress("Muon5Eta", &Muon5Eta);
   Tree->SetBranchAddress("Muon5Phi", &Muon5Phi);
   Tree->SetBranchAddress("Muon5PassTight", &Muon5PassTight);
   Tree->SetBranchAddress("Muon5PassLoose", &Muon5PassLoose);
   Tree->SetBranchAddress("Muon5Isolation", &Muon5Isolation);
   Tree->SetBranchAddress("Muon6PT", &Muon6PT);
   Tree->SetBranchAddress("Muon6Eta", &Muon6Eta);
   Tree->SetBranchAddress("Muon6Phi", &Muon6Phi);
   Tree->SetBranchAddress("Muon6PassTight", &Muon6PassTight);
   Tree->SetBranchAddress("Muon6PassLoose", &Muon6PassLoose);
   Tree->SetBranchAddress("Muon6Isolation", &Muon6Isolation);
   Tree->SetBranchAddress("Muon7PT", &Muon7PT);
   Tree->SetBranchAddress("Muon7Eta", &Muon7Eta);
   Tree->SetBranchAddress("Muon7Phi", &Muon7Phi);
   Tree->SetBranchAddress("Muon7PassTight", &Muon7PassTight);
   Tree->SetBranchAddress("Muon7PassLoose", &Muon7PassLoose);
   Tree->SetBranchAddress("Muon7Isolation", &Muon7Isolation);
   Tree->SetBranchAddress("Muon8PT", &Muon8PT);
   Tree->SetBranchAddress("Muon8Eta", &Muon8Eta);
   Tree->SetBranchAddress("Muon8Phi", &Muon8Phi);
   Tree->SetBranchAddress("Muon8PassTight", &Muon8PassTight);
   Tree->SetBranchAddress("Muon8PassLoose", &Muon8PassLoose);
   Tree->SetBranchAddress("Muon8Isolation", &Muon8Isolation);
   Tree->SetBranchAddress("Muon9PT", &Muon9PT);
   Tree->SetBranchAddress("Muon9Eta", &Muon9Eta);
   Tree->SetBranchAddress("Muon9Phi", &Muon9Phi);
   Tree->SetBranchAddress("Muon9PassTight", &Muon9PassTight);
   Tree->SetBranchAddress("Muon9PassLoose", &Muon9PassLoose);
   Tree->SetBranchAddress("Muon9Isolation", &Muon9Isolation);
   Tree->SetBranchAddress("Muon10PT", &Muon10PT);
   Tree->SetBranchAddress("Muon10Eta", &Muon10Eta);
   Tree->SetBranchAddress("Muon10Phi", &Muon10Phi);
   Tree->SetBranchAddress("Muon10PassTight", &Muon10PassTight);
   Tree->SetBranchAddress("Muon10PassLoose", &Muon10PassLoose);
   Tree->SetBranchAddress("Muon10Isolation", &Muon10Isolation);
   Tree->SetBranchAddress("GoodElectronCount", &GoodElectronCount);
   Tree->SetBranchAddress("GoodElectronCount80", &GoodElectronCount80);
   Tree->SetBranchAddress("GoodElectronCount85", &GoodElectronCount85);
   Tree->SetBranchAddress("GoodElectronCount90", &GoodElectronCount90);
   Tree->SetBranchAddress("GoodElectronCount95", &GoodElectronCount95);
   Tree->SetBranchAddress("Electron1PT", &ElectronPT[0]);
   Tree->SetBranchAddress("Electron1Eta", &ElectronEta[0]);
   Tree->SetBranchAddress("Electron1Phi", &ElectronPhi[0]);
   Tree->SetBranchAddress("Electron1Pass95", &ElectronPass95[0]);
   Tree->SetBranchAddress("Electron1Pass90", &ElectronPass90[0]);
   Tree->SetBranchAddress("Electron1Pass85", &ElectronPass85[0]);
   Tree->SetBranchAddress("Electron1Pass80", &ElectronPass80[0]);
   Tree->SetBranchAddress("Electron1Isolation", &ElectronIsolation[0]);
   Tree->SetBranchAddress("Electron2PT", &ElectronPT[1]);
   Tree->SetBranchAddress("Electron2Eta", &ElectronEta[1]);
   Tree->SetBranchAddress("Electron2Phi", &ElectronPhi[1]);
   Tree->SetBranchAddress("Electron2Pass95", &ElectronPass95[1]);
   Tree->SetBranchAddress("Electron2Pass90", &ElectronPass90[1]);
   Tree->SetBranchAddress("Electron2Pass85", &ElectronPass85[1]);
   Tree->SetBranchAddress("Electron2Pass80", &ElectronPass80[1]);
   Tree->SetBranchAddress("Electron2Isolation", &ElectronIsolation[1]);
   Tree->SetBranchAddress("Electron3PT", &ElectronPT[2]);
   Tree->SetBranchAddress("Electron3Eta", &ElectronEta[2]);
   Tree->SetBranchAddress("Electron3Phi", &ElectronPhi[2]);
   Tree->SetBranchAddress("Electron3Pass95", &ElectronPass95[2]);
   Tree->SetBranchAddress("Electron3Pass90", &ElectronPass90[2]);
   Tree->SetBranchAddress("Electron3Pass85", &ElectronPass85[2]);
   Tree->SetBranchAddress("Electron3Pass80", &ElectronPass80[2]);
   Tree->SetBranchAddress("Electron3Isolation", &ElectronIsolation[2]);
   Tree->SetBranchAddress("Electron4PT", &ElectronPT[3]);
   Tree->SetBranchAddress("Electron4Eta", &ElectronEta[3]);
   Tree->SetBranchAddress("Electron4Phi", &ElectronPhi[3]);
   Tree->SetBranchAddress("Electron4Pass95", &ElectronPass95[3]);
   Tree->SetBranchAddress("Electron4Pass90", &ElectronPass90[3]);
   Tree->SetBranchAddress("Electron4Pass85", &ElectronPass85[3]);
   Tree->SetBranchAddress("Electron4Pass80", &ElectronPass80[3]);
   Tree->SetBranchAddress("Electron4Isolation", &ElectronIsolation[3]);
   Tree->SetBranchAddress("Electron5PT", &ElectronPT[4]);
   Tree->SetBranchAddress("Electron5Eta", &ElectronEta[4]);
   Tree->SetBranchAddress("Electron5Phi", &ElectronPhi[4]);
   Tree->SetBranchAddress("Electron5Pass95", &ElectronPass95[4]);
   Tree->SetBranchAddress("Electron5Pass90", &ElectronPass90[4]);
   Tree->SetBranchAddress("Electron5Pass85", &ElectronPass85[4]);
   Tree->SetBranchAddress("Electron5Pass80", &ElectronPass80[4]);
   Tree->SetBranchAddress("Electron5Isolation", &ElectronIsolation[4]);
   Tree->SetBranchAddress("Electron6PT", &ElectronPT[5]);
   Tree->SetBranchAddress("Electron6Eta", &ElectronEta[5]);
   Tree->SetBranchAddress("Electron6Phi", &ElectronPhi[5]);
   Tree->SetBranchAddress("Electron6Pass95", &ElectronPass95[5]);
   Tree->SetBranchAddress("Electron6Pass90", &ElectronPass90[5]);
   Tree->SetBranchAddress("Electron6Pass85", &ElectronPass85[5]);
   Tree->SetBranchAddress("Electron6Pass80", &ElectronPass80[5]);
   Tree->SetBranchAddress("Electron6Isolation", &ElectronIsolation[5]);
   Tree->SetBranchAddress("Electron7PT", &ElectronPT[6]);
   Tree->SetBranchAddress("Electron7Eta", &ElectronEta[6]);
   Tree->SetBranchAddress("Electron7Phi", &ElectronPhi[6]);
   Tree->SetBranchAddress("Electron7Pass95", &ElectronPass95[6]);
   Tree->SetBranchAddress("Electron7Pass90", &ElectronPass90[6]);
   Tree->SetBranchAddress("Electron7Pass85", &ElectronPass85[6]);
   Tree->SetBranchAddress("Electron7Pass80", &ElectronPass80[6]);
   Tree->SetBranchAddress("Electron7Isolation", &ElectronIsolation[6]);
   Tree->SetBranchAddress("Electron8PT", &ElectronPT[7]);
   Tree->SetBranchAddress("Electron8Eta", &ElectronEta[7]);
   Tree->SetBranchAddress("Electron8Phi", &ElectronPhi[7]);
   Tree->SetBranchAddress("Electron8Pass95", &ElectronPass95[7]);
   Tree->SetBranchAddress("Electron8Pass90", &ElectronPass90[7]);
   Tree->SetBranchAddress("Electron8Pass85", &ElectronPass85[7]);
   Tree->SetBranchAddress("Electron8Pass80", &ElectronPass80[7]);
   Tree->SetBranchAddress("Electron8Isolation", &ElectronIsolation[7]);
   Tree->SetBranchAddress("Electron9PT", &ElectronPT[8]);
   Tree->SetBranchAddress("Electron9Eta", &ElectronEta[8]);
   Tree->SetBranchAddress("Electron9Phi", &ElectronPhi[8]);
   Tree->SetBranchAddress("Electron9Pass95", &ElectronPass95[8]);
   Tree->SetBranchAddress("Electron9Pass90", &ElectronPass90[8]);
   Tree->SetBranchAddress("Electron9Pass85", &ElectronPass85[8]);
   Tree->SetBranchAddress("Electron9Pass80", &ElectronPass80[8]);
   Tree->SetBranchAddress("Electron9Isolation", &ElectronIsolation[8]);
   Tree->SetBranchAddress("Electron10PT", &ElectronPT[9]);
   Tree->SetBranchAddress("Electron10Eta", &ElectronEta[9]);
   Tree->SetBranchAddress("Electron10Phi", &ElectronPhi[9]);
   Tree->SetBranchAddress("Electron10Pass95", &ElectronPass95[9]);
   Tree->SetBranchAddress("Electron10Pass90", &ElectronPass90[9]);
   Tree->SetBranchAddress("Electron10Pass85", &ElectronPass85[9]);
   Tree->SetBranchAddress("Electron10Pass80", &ElectronPass80[9]);
   Tree->SetBranchAddress("Electron10Isolation", &ElectronIsolation[9]);

   Tree->SetBranchAddress("AllElectronCount", &AllElectronCount);
   for(int i = 0; i < 10; i++)
   {
      Tree->SetBranchAddress(Form("AllElectron%dPT", i + 1), &AllElectronPT[i]);
      Tree->SetBranchAddress(Form("AllElectron%dEta", i + 1), &AllElectronEta[i]);
      Tree->SetBranchAddress(Form("AllElectron%dPhi", i + 1), &AllElectronPhi[i]);
      Tree->SetBranchAddress(Form("AllElectron%dPass95", i + 1), &AllElectronPass95[i]);
      Tree->SetBranchAddress(Form("AllElectron%dPass90", i + 1), &AllElectronPass90[i]);
      Tree->SetBranchAddress(Form("AllElectron%dPass85", i + 1), &AllElectronPass85[i]);
      Tree->SetBranchAddress(Form("AllElectron%dPass80", i + 1), &AllElectronPass80[i]);
      Tree->SetBranchAddress(Form("AllElectron%dIsolation", i + 1), &AllElectronIsolation[i]);
      Tree->SetBranchAddress(Form("AllElectron%dConversionDistance", i + 1), &AllElectronConversionDistance[i]);
      Tree->SetBranchAddress(Form("AllElectron%dConversionDeltaCotTheta", i + 1),
         &AllElectronConversionDeltaCotTheta[i]);
      Tree->SetBranchAddress(Form("AllElectron%dSigmaIEtaIEta", i + 1), &AllElectronSigmaIEtaIEta[i]);
   }
   
   Tree->SetBranchAddress("PassHLT", &PassHLT);
   Tree->SetBranchAddress("PassNoiseFilter", &PassNoiseFilter);
   Tree->SetBranchAddress("PassCaloJetID", &PassCaloJetID);
   Tree->SetBranchAddress("PassCaloJet60", &PassCaloJet60);
   Tree->SetBranchAddress("PassPFJetID", &PassPFJetID);
   Tree->SetBranchAddress("PassPFJet60", &PassPFJet60);
   Tree->SetBranchAddress("PassDiJetAve30", &PassDiJetAve30);
   Tree->SetBranchAddress("PassDiJetAve60", &PassDiJetAve60);
   Tree->SetBranchAddress("PassDiJetAve80", &PassDiJetAve80);
   Tree->SetBranchAddress("PassDiJetAve110", &PassDiJetAve110);
   Tree->SetBranchAddress("PassDiJetAve150", &PassDiJetAve150);
   Tree->SetBranchAddress("PassDiJetAve190", &PassDiJetAve190);
   Tree->SetBranchAddress("PassDiJetAve240", &PassDiJetAve240);
   Tree->SetBranchAddress("PassDiJetAve300", &PassDiJetAve300);
   Tree->SetBranchAddress("PassDiJetAve370", &PassDiJetAve370);
   Tree->SetBranchAddress("PassDiJetAve15U", &PassDiJetAve15U);
   Tree->SetBranchAddress("PassDiJetAve30U", &PassDiJetAve30U);
   Tree->SetBranchAddress("PassDiJetAve50U", &PassDiJetAve50U);
   Tree->SetBranchAddress("PassDiJetAve70U", &PassDiJetAve70U);
   Tree->SetBranchAddress("PassDiJetAve100U", &PassDiJetAve100U);
   Tree->SetBranchAddress("PassDiJetAve140U", &PassDiJetAve140U);
   Tree->SetBranchAddress("PassDiJetAve180U", &PassDiJetAve180U);
   Tree->SetBranchAddress("PassDiJetAve300U", &PassDiJetAve300U);
   Tree->SetBranchAddress("PassSingleMu3", &PassSingleMu3);
   Tree->SetBranchAddress("PassSingleMu5", &PassSingleMu5);
   Tree->SetBranchAddress("PassSingleMu8", &PassSingleMu8);
   Tree->SetBranchAddress("PassSingleMu12", &PassSingleMu12);
   Tree->SetBranchAddress("PassSingleMu15", &PassSingleMu15);
   Tree->SetBranchAddress("PassSingleMu20", &PassSingleMu20);
   Tree->SetBranchAddress("PassSingleMu24", &PassSingleMu24);
   Tree->SetBranchAddress("PassSingleMu30", &PassSingleMu30);
   Tree->SetBranchAddress("PassSingleMu40", &PassSingleMu40);
   Tree->SetBranchAddress("PassSingleMu100", &PassSingleMu100);
   Tree->SetBranchAddress("PassR020MR500", &PassR020MR500);
   Tree->SetBranchAddress("PassR020MR550", &PassR020MR550);
   Tree->SetBranchAddress("PassR023MR550", &PassR023MR550);
   Tree->SetBranchAddress("PassR025MR400", &PassR025MR400);
   Tree->SetBranchAddress("PassR025MR450", &PassR025MR450);
   Tree->SetBranchAddress("PassR029MR450", &PassR029MR450);
   Tree->SetBranchAddress("PassR033MR300", &PassR033MR300);
   Tree->SetBranchAddress("PassR033MR350", &PassR033MR350);
   Tree->SetBranchAddress("PassR036MR350", &PassR036MR350);
   Tree->SetBranchAddress("PassR038MR200", &PassR038MR200);
   Tree->SetBranchAddress("PassR038MR250", &PassR038MR250);
   Tree->SetBranchAddress("PassR042MR250", &PassR042MR250);
   Tree->SetBranchAddress("PassEleL10R020MR200", &PassEleL10R020MR200);
   Tree->SetBranchAddress("PassEleL10R025MR200", &PassEleL10R025MR200);
   Tree->SetBranchAddress("PassEleL10R029MR200", &PassEleL10R029MR200);
   Tree->SetBranchAddress("PassEleT10R020MR200", &PassEleT10R020MR200);
   Tree->SetBranchAddress("PassMu8R020MR200", &PassMu8R020MR200);
   Tree->SetBranchAddress("PassMu8R025MR200", &PassMu8R025MR200);
   Tree->SetBranchAddress("PassMu8R029MR200", &PassMu8R029MR200);
   Tree->SetBranchAddress("PassMu17Mu8", &PassMu17Mu8);
   Tree->SetBranchAddress("PassMu13Mu8", &PassMu13Mu8);
   Tree->SetBranchAddress("PassMu8EleL17", &PassMu8EleL17);
   Tree->SetBranchAddress("PassMu17EleL8", &PassMu17EleL8);
}
   
void TreeRecord::Branch(TTree *Tree)
{
   // General
   Tree->Branch("RunNumber", &RunNumber, "RunNumber/D");
   Tree->Branch("EventNumber", &EventNumber, "EventNumber/D");
   Tree->Branch("BunchCrossing", &BunchCrossing, "BunchCrossing/D");
   Tree->Branch("LumiSection", &LumiSection, "LumiSection/D");
   Tree->Branch("Orbit", &Orbit, "Orbit/D");
   Tree->Branch("PileUp", &PileUp, "PileUp/I");

   // calo jets
   Tree->Branch("CaloJetCount", &CaloJetCount, "CaloJetCount/I");
   Tree->Branch("CaloJetCount30", &CaloJetCount30, "CaloJetCount30/I");
   Tree->Branch("CaloJetCount50", &CaloJetCount50, "CaloJetCount50/I");
   Tree->Branch("CaloJetCount100", &CaloJetCount100, "CaloJetCount100/I");
   Tree->Branch("CaloJetE", CaloJetE, "CaloJetE[100]/D");
   Tree->Branch("CaloJetPT", CaloJetPT, "CaloJetPT[100]/D");
   Tree->Branch("CaloJetEta", CaloJetEta, "CaloJetEta[100]/D");
   Tree->Branch("CaloJetPhi", CaloJetPhi, "CaloJetPhi[100]/D");
   Tree->Branch("CaloJetCSVTag", CaloJetCSVTag, "CaloJetCSVTag[100]/D");
   Tree->Branch("CaloJetCSVMTag", CaloJetCSVMTag, "CaloJetCSVMTag[100]/D");
   Tree->Branch("CaloJetSSVHETag", CaloJetSSVHETag, "CaloJetSSVHETag[100]/D");
   Tree->Branch("CaloJetSSVHPTag", CaloJetSSVHPTag, "CaloJetSSVHPTag[100]/D");
   Tree->Branch("CaloJetTCHPTag", CaloJetTCHPTag, "CaloJetTCHPTag[100]/D");
   Tree->Branch("CaloJetTCHETag", CaloJetTCHETag, "CaloJetTCHETag[100]/D");

   // PF jets
   Tree->Branch("PFJetCount", &PFJetCount, "PFJetCount/I");
   Tree->Branch("PFJetCount30", &PFJetCount30, "PFJetCount30/I");
   Tree->Branch("PFJetCount50", &PFJetCount50, "PFJetCount50/I");
   Tree->Branch("PFJetCount100", &PFJetCount100, "PFJetCount100/I");
   Tree->Branch("PFJetE", PFJetE, "PFJetE[100]/D");
   Tree->Branch("PFJetPT", PFJetPT, "PFJetPT[100]/D");
   Tree->Branch("PFJetEta", PFJetEta, "PFJetEta[100]/D");
   Tree->Branch("PFJetPhi", PFJetPhi, "PFJetPhi[100]/D");
   Tree->Branch("PFJetCSVTag", PFJetCSVTag, "PFJetCSVTag[100]/D");
   Tree->Branch("PFJetCSVMTag", PFJetCSVMTag, "PFJetCSVMTag[100]/D");
   Tree->Branch("PFJetSSVHETag", PFJetSSVHETag, "PFJetSSVHETag[100]/D");
   Tree->Branch("PFJetSSVHPMTag", PFJetSSVHPTag, "PFJetSSVHPMTag[100]/D");
   Tree->Branch("PFJetTCHPTag", PFJetTCHPTag, "PFJetTCHPTag[100]/D");
   Tree->Branch("PFJetTCHETag", PFJetTCHETag, "PFJetTCHETag[100]/D");

   // Primary vertex
   Tree->Branch("PrimaryVertexCount", &PrimaryVertexCount, "PrimaryVertexCount/I");
   Tree->Branch("PrimaryVertexMaxSumPT", &PrimaryVertexMaxSumPT, "PrimaryVertexMaxSumPT/D");

   // Missing energy
   Tree->Branch("CaloMET", CaloMET, "CaloMET[2]/D");
   Tree->Branch("PFMET", PFMET, "PFMET[2]/D");

   // Muons
   Tree->Branch("GoodMuonCount", &GoodMuonCount, "GoodMuonCount/I");
   Tree->Branch("GoodMuonCountTight", &GoodMuonCountTight, "GoodMuonCountTight/I");
   Tree->Branch("GoodMuonCountLoose", &GoodMuonCountLoose, "GoodMuonCountLoose/I");

   Tree->Branch("Muon1PT", &Muon1PT, "Muon1PT/D");
   Tree->Branch("Muon1Eta", &Muon1Eta, "Muon1Eta/D");
   Tree->Branch("Muon1Phi", &Muon1Phi, "Muon1Phi/D");
   Tree->Branch("Muon1PassTight", &Muon1PassTight, "Muon1PassTight/O");
   Tree->Branch("Muon1PassLoose", &Muon1PassLoose, "Muon1PassLoose/O");
   Tree->Branch("Muon1Isolation", &Muon1Isolation, "Muon1Isolation/F");
   Tree->Branch("Muon2PT", &Muon2PT, "Muon2PT/D");
   Tree->Branch("Muon2Eta", &Muon2Eta, "Muon2Eta/D");
   Tree->Branch("Muon2Phi", &Muon2Phi, "Muon2Phi/D");
   Tree->Branch("Muon2PassTight", &Muon2PassTight, "Muon2PassTight/O");
   Tree->Branch("Muon2PassLoose", &Muon2PassLoose, "Muon2PassLoose/O");
   Tree->Branch("Muon2Isolation", &Muon2Isolation, "Muon2Isolation/F");
   Tree->Branch("Muon3PT", &Muon3PT, "Muon3PT/D");
   Tree->Branch("Muon3Eta", &Muon3Eta, "Muon3Eta/D");
   Tree->Branch("Muon3Phi", &Muon3Phi, "Muon3Phi/D");
   Tree->Branch("Muon3PassTight", &Muon3PassTight, "Muon3PassTight/O");
   Tree->Branch("Muon3PassLoose", &Muon3PassLoose, "Muon3PassLoose/O");
   Tree->Branch("Muon3Isolation", &Muon3Isolation, "Muon3Isolation/F");
   Tree->Branch("Muon4PT", &Muon4PT, "Muon4PT/D");
   Tree->Branch("Muon4Eta", &Muon4Eta, "Muon4Eta/D");
   Tree->Branch("Muon4Phi", &Muon4Phi, "Muon4Phi/D");
   Tree->Branch("Muon4PassTight", &Muon4PassTight, "Muon4PassTight/O");
   Tree->Branch("Muon4PassLoose", &Muon4PassLoose, "Muon4PassLoose/O");
   Tree->Branch("Muon4Isolation", &Muon4Isolation, "Muon4Isolation/F");
   Tree->Branch("Muon5PT", &Muon5PT, "Muon5PT/D");
   Tree->Branch("Muon5Eta", &Muon5Eta, "Muon5Eta/D");
   Tree->Branch("Muon5Phi", &Muon5Phi, "Muon5Phi/D");
   Tree->Branch("Muon5PassTight", &Muon5PassTight, "Muon5PassTight/O");
   Tree->Branch("Muon5PassLoose", &Muon5PassLoose, "Muon5PassLoose/O");
   Tree->Branch("Muon5Isolation", &Muon5Isolation, "Muon5Isolation/F");
   Tree->Branch("Muon6PT", &Muon6PT, "Muon6PT/D");
   Tree->Branch("Muon6Eta", &Muon6Eta, "Muon6Eta/D");
   Tree->Branch("Muon6Phi", &Muon6Phi, "Muon6Phi/D");
   Tree->Branch("Muon6PassTight", &Muon6PassTight, "Muon6PassTight/O");
   Tree->Branch("Muon6PassLoose", &Muon6PassLoose, "Muon6PassLoose/O");
   Tree->Branch("Muon6Isolation", &Muon6Isolation, "Muon6Isolation/F");
   Tree->Branch("Muon7PT", &Muon7PT, "Muon7PT/D");
   Tree->Branch("Muon7Eta", &Muon7Eta, "Muon7Eta/D");
   Tree->Branch("Muon7Phi", &Muon7Phi, "Muon7Phi/D");
   Tree->Branch("Muon7PassTight", &Muon7PassTight, "Muon7PassTight/O");
   Tree->Branch("Muon7PassLoose", &Muon7PassLoose, "Muon7PassLoose/O");
   Tree->Branch("Muon7Isolation", &Muon7Isolation, "Muon7Isolation/F");
   Tree->Branch("Muon8PT", &Muon8PT, "Muon8PT/D");
   Tree->Branch("Muon8Eta", &Muon8Eta, "Muon8Eta/D");
   Tree->Branch("Muon8Phi", &Muon8Phi, "Muon8Phi/D");
   Tree->Branch("Muon8PassTight", &Muon8PassTight, "Muon8PassTight/O");
   Tree->Branch("Muon8PassLoose", &Muon8PassLoose, "Muon8PassLoose/O");
   Tree->Branch("Muon8Isolation", &Muon8Isolation, "Muon8Isolation/F");
   Tree->Branch("Muon9PT", &Muon9PT, "Muon9PT/D");
   Tree->Branch("Muon9Eta", &Muon9Eta, "Muon9Eta/D");
   Tree->Branch("Muon9Phi", &Muon9Phi, "Muon9Phi/D");
   Tree->Branch("Muon9PassTight", &Muon9PassTight, "Muon9PassTight/O");
   Tree->Branch("Muon9PassLoose", &Muon9PassLoose, "Muon9PassLoose/O");
   Tree->Branch("Muon9Isolation", &Muon9Isolation, "Muon9Isolation/F");
   Tree->Branch("Muon10PT", &Muon10PT, "Muon10PT/D");
   Tree->Branch("Muon10Eta", &Muon10Eta, "Muon10Eta/D");
   Tree->Branch("Muon10Phi", &Muon10Phi, "Muon10Phi/D");
   Tree->Branch("Muon10PassTight", &Muon10PassTight, "Muon10PassTight/O");
   Tree->Branch("Muon10PassLoose", &Muon10PassLoose, "Muon10PassLoose/O");
   Tree->Branch("Muon10Isolation", &Muon10Isolation, "Muon10Isolation/F");

   // Electrons
   Tree->Branch("GoodElectronCount", &GoodElectronCount, "GoodElectronCount/I");
   Tree->Branch("GoodElectronCount80", &GoodElectronCount80, "GoodElectronCount80/I");
   Tree->Branch("GoodElectronCount85", &GoodElectronCount85, "GoodElectronCount85/I");
   Tree->Branch("GoodElectronCount90", &GoodElectronCount90, "GoodElectronCount90/I");
   Tree->Branch("GoodElectronCount95", &GoodElectronCount95, "GoodElectronCount95/I");

   for(int i = 0; i < 10; i++)
   {
      Tree->Branch(Form("Electron%dPT", i + 1), &ElectronPT[i], Form("Electron%dPT/D", i + 1));
      Tree->Branch(Form("Electron%dEta", i + 1), &ElectronEta[i], Form("Electron%dEta/D", i + 1));
      Tree->Branch(Form("Electron%dPhi", i + 1), &ElectronPhi[i], Form("Electron%dPhi/D", i + 1));
      Tree->Branch(Form("Electron%dPass95", i + 1), &ElectronPass95[i], Form("Electron%dPass95/O", i + 1));
      Tree->Branch(Form("Electron%dPass90", i + 1), &ElectronPass90[i], Form("Electron%dPass90/O", i + 1));
      Tree->Branch(Form("Electron%dPass85", i + 1), &ElectronPass85[i], Form("Electron%dPass85/O", i + 1));
      Tree->Branch(Form("Electron%dPass80", i + 1), &ElectronPass80[i], Form("Electron%dPass80/O", i + 1));
      Tree->Branch(Form("Electron%dIsolation", i + 1), &ElectronIsolation[i],
         Form("Electron%dIsolation/O", i + 1));
   }

   Tree->Branch("AllElectronCount", &AllElectronCount, "AllElectronCount/I");

   for(int i = 0; i < 10; i++)
   {
      Tree->Branch(Form("AllElectron%dPT", i + 1), &AllElectronPT[i], Form("AllElectron%dPT/D", i + 1));
      Tree->Branch(Form("AllElectron%dEta", i + 1), &AllElectronEta[i], Form("AllElectron%dEta/D", i + 1));
      Tree->Branch(Form("AllElectron%dPhi", i + 1), &AllElectronPhi[i], Form("AllElectron%dPhi/D", i + 1));
      Tree->Branch(Form("AllElectron%dPass95", i + 1), &AllElectronPass95[i],
         Form("AllElectron%dPass95/O", i + 1));
      Tree->Branch(Form("AllElectron%dPass90", i + 1), &AllElectronPass90[i],
         Form("AllElectron%dPass90/O", i + 1));
      Tree->Branch(Form("AllElectron%dPass85", i + 1), &AllElectronPass85[i],
         Form("AllElectron%dPass85/O", i + 1));
      Tree->Branch(Form("AllElectron%dPass80", i + 1), &AllElectronPass80[i],
         Form("AllElectron%dPass80/O", i + 1));
      Tree->Branch(Form("AllElectron%dIsolation", i + 1), &AllElectronIsolation[i],
         Form("AllElectron%dIsolation/O", i + 1));
      Tree->Branch(Form("AllElectron%dConversionDistance", i + 1), &AllElectronConversionDistance[i],
         Form("AllElectron%dConversionDistance/O", i + 1));
      Tree->Branch(Form("AllElectron%dConversionDeltaCotTheta", i + 1), &AllElectronConversionDeltaCotTheta[i],
         Form("AllElectron%dConversionDeltaCotTheta/O", i + 1));
      Tree->Branch(Form("AllElectron%dSigmaIEtaIEta", i + 1), &AllElectronSigmaIEtaIEta[i],
         Form("AllElectron%dSigmaIEtaIEta/O", i + 1));
   }
   
   // baseline event selection
   Tree->Branch("PassHLT", &PassHLT, "PassHLT/O");
   Tree->Branch("PassNoiseFilter", &PassNoiseFilter, "PassNoiseFilter/O");
   Tree->Branch("PassCaloJetID", &PassCaloJetID, "PassCaloJetID/O");
   Tree->Branch("PassCaloJet60", &PassCaloJet60, "PassCaloJet60/O");
   Tree->Branch("PassPFJetID", &PassPFJetID, "PassPFJetID/O");
   Tree->Branch("PassPFJet60", &PassPFJet60, "PassPFJet60/O");

   // auxiliary HLT bits
   Tree->Branch("PassDiJetAve30", &PassDiJetAve30, "PassDiJetAve30/O");
   Tree->Branch("PassDiJetAve60", &PassDiJetAve60, "PassDiJetAve60/O");
   Tree->Branch("PassDiJetAve80", &PassDiJetAve80, "PassDiJetAve80/O");
   Tree->Branch("PassDiJetAve110", &PassDiJetAve110, "PassDiJetAve110/O");
   Tree->Branch("PassDiJetAve150", &PassDiJetAve150, "PassDiJetAve150/O");
   Tree->Branch("PassDiJetAve190", &PassDiJetAve190, "PassDiJetAve190/O");
   Tree->Branch("PassDiJetAve240", &PassDiJetAve240, "PassDiJetAve240/O");
   Tree->Branch("PassDiJetAve300", &PassDiJetAve300, "PassDiJetAve300/O");
   Tree->Branch("PassDiJetAve370", &PassDiJetAve370, "PassDiJetAve370/O");

   Tree->Branch("PassDiJetAve15U", &PassDiJetAve15U, "PassDiJetAve15U/O");
   Tree->Branch("PassDiJetAve30U", &PassDiJetAve30U, "PassDiJetAve30U/O");
   Tree->Branch("PassDiJetAve50U", &PassDiJetAve50U, "PassDiJetAve50U/O");
   Tree->Branch("PassDiJetAve70U", &PassDiJetAve70U, "PassDiJetAve70U/O");
   Tree->Branch("PassDiJetAve100U", &PassDiJetAve100U, "PassDiJetAve100U/O");
   Tree->Branch("PassDiJetAve140U", &PassDiJetAve140U, "PassDiJetAve140U/O");
   Tree->Branch("PassDiJetAve180U", &PassDiJetAve180U, "PassDiJetAve180U/O");
   Tree->Branch("PassDiJetAve300U", &PassDiJetAve300U, "PassDiJetAve300U/O");

   Tree->Branch("PassSingleMu3", &PassSingleMu3, "PassSingleMu3/O");
   Tree->Branch("PassSingleMu5", &PassSingleMu5, "PassSingleMu5/O");
   Tree->Branch("PassSingleMu8", &PassSingleMu8, "PassSingleMu8/O");
   Tree->Branch("PassSingleMu12", &PassSingleMu12, "PassSingleMu12/O");
   Tree->Branch("PassSingleMu15", &PassSingleMu15, "PassSingleMu15/O");
   Tree->Branch("PassSingleMu20", &PassSingleMu20, "PassSingleMu20/O");
   Tree->Branch("PassSingleMu24", &PassSingleMu24, "PassSingleMu24/O");
   Tree->Branch("PassSingleMu30", &PassSingleMu30, "PassSingleMu30/O");
   Tree->Branch("PassSingleMu40", &PassSingleMu40, "PassSingleMu40/O");
   Tree->Branch("PassSingleMu100", &PassSingleMu100, "PassSingleMu100/O");

   Tree->Branch("PassR020MR500", &PassR020MR500, "PassR020MR500/O");
   Tree->Branch("PassR020MR550", &PassR020MR550, "PassR020MR550/O");
   Tree->Branch("PassR023MR550", &PassR023MR550, "PassR023MR550/O");
   Tree->Branch("PassR025MR400", &PassR025MR400, "PassR025MR400/O");
   Tree->Branch("PassR025MR450", &PassR025MR450, "PassR025MR450/O");
   Tree->Branch("PassR029MR450", &PassR029MR450, "PassR029MR450/O");
   Tree->Branch("PassR033MR300", &PassR033MR300, "PassR033MR300/O");
   Tree->Branch("PassR033MR350", &PassR033MR350, "PassR033MR350/O");
   Tree->Branch("PassR036MR350", &PassR036MR350, "PassR036MR350/O");
   Tree->Branch("PassR038MR200", &PassR038MR200, "PassR038MR200/O");
   Tree->Branch("PassR038MR250", &PassR038MR250, "PassR038MR250/O");
   Tree->Branch("PassR042MR250", &PassR042MR250, "PassR042MR250/O");

   Tree->Branch("PassEleL10R020MR200", &PassEleL10R020MR200, "PassEleL10R020MR200/O");
   Tree->Branch("PassEleL10R025MR200", &PassEleL10R025MR200, "PassEleL10R025MR200/O");
   Tree->Branch("PassEleL10R029MR200", &PassEleL10R029MR200, "PassEleL10R029MR200/O");
   Tree->Branch("PassEleT10R020MR200", &PassEleT10R020MR200, "PassEleT10R020MR200/O");

   Tree->Branch("PassMu8R020MR200", &PassMu8R020MR200, "PassMu8R020MR200/O");
   Tree->Branch("PassMu8R025MR200", &PassMu8R025MR200, "PassMu8R025MR200/O");
   Tree->Branch("PassMu8R029MR200", &PassMu8R029MR200, "PassMu8R029MR200/O");

   Tree->Branch("PassMu17Mu8", &PassMu17Mu8, "PassMu17Mu8/O");
   Tree->Branch("PassMu13Mu8", &PassMu13Mu8, "PassMu13Mu8/O");

   Tree->Branch("PassMu8EleL17", &PassMu8EleL17, "PassMu8EleL17/O");
   Tree->Branch("PassMu17EleL8", &PassMu17EleL8, "PassMu17EleL8/O");
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



