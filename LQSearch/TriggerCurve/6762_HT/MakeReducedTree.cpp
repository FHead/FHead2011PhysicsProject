#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "TChain.h"
#include "TTree.h"
#include "TFile.h"

#include "TauHelperFunctions2.h"

int main();
bool CheckBit(int firedTrg[], int bit);

int main()
{
   TChain Tree("ntp1", "ntp1");
   // Tree.AddFile("AllHT.root");
   Tree.AddFile("AllJets.root");

   // TFile F("ReducedTree.root", "RECREATE");
   TFile F("ReducedTreeJets.root", "RECREATE");
   TTree OutputTree("OutputTree", "OutputTree");

   int nTrg;
   int firedTrg[20];
   int nHLT;
   int indexHLT[500];
   vector<string> *nameHLT = NULL;

   Tree.SetBranchAddress("nTrg", &nTrg);
   Tree.SetBranchAddress("firedTrg", firedTrg);
   Tree.SetBranchAddress("nHLT", &nHLT);
   Tree.SetBranchAddress("nameHLT", &nameHLT);
   Tree.SetBranchAddress("indexHLT", indexHLT);

   int nAK5Jet;
   float energyAK5Jet[200];
   float phiAK5Jet[200];
   float etaAK5Jet[200];
   float pxAK5Jet[200];
   float pyAK5Jet[200];
   float pzAK5Jet[200];
   float pxMet[1];
   float pyMet[1];
   float TCHE[200];
   float TCHP[200];
   float SSVHE[200];
   float SSVHP[200];

   Tree.SetBranchAddress("nAK5Jet", &nAK5Jet);
   Tree.SetBranchAddress("energyAK5Jet", energyAK5Jet);
   Tree.SetBranchAddress("phiAK5Jet", phiAK5Jet);
   Tree.SetBranchAddress("etaAK5Jet", etaAK5Jet);
   Tree.SetBranchAddress("pxAK5Jet", pxAK5Jet);
   Tree.SetBranchAddress("pyAK5Jet", pyAK5Jet);
   Tree.SetBranchAddress("pzAK5Jet", pzAK5Jet);
   Tree.SetBranchAddress("pxMet", pxMet);
   Tree.SetBranchAddress("pyMet", pyMet);
   Tree.SetBranchAddress("trackCountingHighEffBJetTagsAK5Jet", TCHE);
   Tree.SetBranchAddress("trackCountingHighPurBJetTagsAK5Jet", TCHP);
   Tree.SetBranchAddress("simpleSecondaryVertexHighEffBJetTagsAK5Jet", SSVHE);
   Tree.SetBranchAddress("simpleSecondaryVertexHighPurBJetTagsAK5Jet", SSVHP);

   bool PassDiJetAve60;
   bool PassDiJetAve80;
   bool PassDiJetAve110;
   bool PassDiJetAve150;
   bool PassDiJetAve190;
   bool PassDiJetAve240;
   bool PassDiJetAve300;
   bool PassR038MR200;
   bool PassR038MR250;
   bool PassR033MR300;
   bool PassR033MR350;
   bool PassR025MR400;
   bool PassR025MR450;
   bool PassR020MR500;
   bool PassR020MR550;
   bool PassR014MR150;
   bool PassR020MR150;
   bool PassR025MR150;
   bool PassR014MR450BTag;
   bool PassR020MR350BTag;
   bool PassR025MR250BTag;
   double MaxTCHE;
   double SecondMaxTCHE;
   double MaxTCHP;
   double SecondMaxTCHP;
   double MaxSSVHE;
   double SecondMaxSSVHE;
   double MaxSSVHP;
   double SecondMaxSSVHP;
   double MR;
   double R;

   OutputTree.Branch("PassDiJetAve60", &PassDiJetAve60, "PassDiJetAve60/O");
   OutputTree.Branch("PassDiJetAve80", &PassDiJetAve80, "PassDiJetAve80/O");
   OutputTree.Branch("PassDiJetAve110", &PassDiJetAve110, "PassDiJetAve110/O");
   OutputTree.Branch("PassDiJetAve150", &PassDiJetAve150, "PassDiJetAve150/O");
   OutputTree.Branch("PassDiJetAve190", &PassDiJetAve190, "PassDiJetAve190/O");
   OutputTree.Branch("PassDiJetAve240", &PassDiJetAve240, "PassDiJetAve240/O");
   OutputTree.Branch("PassDiJetAve300", &PassDiJetAve300, "PassDiJetAve300/O");
   OutputTree.Branch("PassR038MR200", &PassR038MR200, "PassR038MR200/O");
   OutputTree.Branch("PassR038MR250", &PassR038MR250, "PassR038MR250/O");
   OutputTree.Branch("PassR033MR300", &PassR033MR300, "PassR033MR300/O");
   OutputTree.Branch("PassR033MR350", &PassR033MR350, "PassR033MR350/O");
   OutputTree.Branch("PassR025MR400", &PassR025MR400, "PassR025MR400/O");
   OutputTree.Branch("PassR025MR450", &PassR025MR450, "PassR025MR450/O");
   OutputTree.Branch("PassR020MR500", &PassR020MR500, "PassR020MR500/O");
   OutputTree.Branch("PassR020MR550", &PassR020MR550, "PassR020MR550/O");
   OutputTree.Branch("PassR014MR150", &PassR014MR150, "PassR014MR150/O");
   OutputTree.Branch("PassR020MR150", &PassR020MR150, "PassR020MR150/O");
   OutputTree.Branch("PassR025MR150", &PassR025MR150, "PassR025MR150/O");
   OutputTree.Branch("PassR014MR450BTag", &PassR014MR450BTag, "PassR014MR450BTag/O");
   OutputTree.Branch("PassR020MR350BTag", &PassR020MR350BTag, "PassR020MR350BTag/O");
   OutputTree.Branch("PassR025MR250BTag", &PassR025MR250BTag, "PassR025MR250BTag/O");
   OutputTree.Branch("MaxTCHE", &MaxTCHE, "MaxTCHE/D");
   OutputTree.Branch("SecondMaxTCHE", &SecondMaxTCHE, "SecondMaxTCHE/D");
   OutputTree.Branch("MaxTCHP", &MaxTCHP, "MaxTCHP/D");
   OutputTree.Branch("SecondMaxTCHP", &SecondMaxTCHP, "SecondMaxTCHP/D");
   OutputTree.Branch("MaxSSVHE", &MaxSSVHE, "MaxSSVHE/D");
   OutputTree.Branch("SecondMaxSSVHE", &SecondMaxSSVHE, "SecondMaxSSVHE/D");
   OutputTree.Branch("MaxSSVHP", &MaxSSVHP, "MaxSSVHP/D");
   OutputTree.Branch("SecondMaxSSVHP", &SecondMaxSSVHP, "SecondMaxSSVHP/D");
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");

   int EntryCount = Tree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      if((i + 1) % 10000 == 0)
         cout << "Processing event " << i + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(i);

      MaxTCHE = -1;
      SecondMaxTCHE = -1;
      MaxTCHP = -1;
      SecondMaxTCHP = -1;
      MaxSSVHE = -1;
      SecondMaxSSVHE = -1;
      MaxSSVHP = -1;
      SecondMaxSSVHP = -1;

      int DiJetAve60Index = -1;
      int DiJetAve80Index = -1;
      int DiJetAve110Index = -1;
      int DiJetAve150Index = -1;
      int DiJetAve190Index = -1;
      int DiJetAve240Index = -1;
      int DiJetAve300Index = -1;
      int R038MR200Index = -1;
      int R038MR250Index = -1;
      int R033MR300Index = -1;
      int R033MR350Index = -1;
      int R025MR400Index = -1;
      int R025MR450Index = -1;
      int R020MR500Index = -1;
      int R020MR550Index = -1;
      int R014MR150Index = -1;
      int R020MR150Index = -1;
      int R025MR150Index = -1;
      int R014MR450IndexBTag = -1;
      int R020MR350IndexBTag = -1;
      int R025MR250IndexBTag = -1;

      for(int j = 0; j < nHLT; j++)
      {
         if((*nameHLT)[j].find("HLT_DiJetAve60") != string::npos)
            DiJetAve60Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve80") != string::npos)
            DiJetAve80Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve110") != string::npos)
            DiJetAve110Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve150") != string::npos)
            DiJetAve150Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve190") != string::npos)
            DiJetAve190Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve240") != string::npos)
            DiJetAve240Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_DiJetAve300") != string::npos)
            DiJetAve300Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R038_MR200") != string::npos)
            R038MR200Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R038_MR250") != string::npos)
            R038MR250Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R033_MR300") != string::npos)
            R033MR300Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R033_MR350") != string::npos)
            R033MR350Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R025_MR400") != string::npos)
            R025MR400Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R025_MR450") != string::npos)
            R025MR450Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R020_MR500") != string::npos)
            R020MR500Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R020_MR550") != string::npos)
            R020MR550Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R014_MR150") != string::npos)
            R014MR150Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R020_MR150") != string::npos)
            R020MR150Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R025_MR150") != string::npos)
            R025MR150Index = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R014_MR450_CentralJet40_BTagIP") != string::npos)
            R014MR450IndexBTag = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R020_MR350_CentralJet40_BTagIP") != string::npos)
            R020MR350IndexBTag = indexHLT[j];
         if((*nameHLT)[j].find("HLT_R025_MR250_CentralJet40_BTagIP") != string::npos)
            R025MR250IndexBTag = indexHLT[j];
      }

      PassDiJetAve60 = CheckBit(firedTrg, DiJetAve60Index);
      PassDiJetAve80 = CheckBit(firedTrg, DiJetAve80Index);
      PassDiJetAve110 = CheckBit(firedTrg, DiJetAve110Index);
      PassDiJetAve150 = CheckBit(firedTrg, DiJetAve150Index);
      PassDiJetAve190 = CheckBit(firedTrg, DiJetAve190Index);
      PassDiJetAve240 = CheckBit(firedTrg, DiJetAve240Index);
      PassDiJetAve300 = CheckBit(firedTrg, DiJetAve300Index);
      PassR038MR200 = CheckBit(firedTrg, R038MR200Index);
      PassR038MR250 = CheckBit(firedTrg, R038MR250Index);
      PassR033MR300 = CheckBit(firedTrg, R033MR300Index);
      PassR033MR350 = CheckBit(firedTrg, R033MR350Index);
      PassR025MR400 = CheckBit(firedTrg, R025MR400Index);
      PassR025MR450 = CheckBit(firedTrg, R025MR450Index);
      PassR020MR500 = CheckBit(firedTrg, R020MR500Index);
      PassR020MR550 = CheckBit(firedTrg, R020MR550Index);
      PassR014MR150 = CheckBit(firedTrg, R014MR150Index);
      PassR020MR150 = CheckBit(firedTrg, R020MR150Index);
      PassR025MR150 = CheckBit(firedTrg, R025MR150Index);
      PassR014MR450BTag = CheckBit(firedTrg, R014MR450IndexBTag);
      PassR020MR350BTag = CheckBit(firedTrg, R020MR350IndexBTag);
      PassR025MR250BTag = CheckBit(firedTrg, R025MR250IndexBTag);

      vector<FourVector> Jets;
      for(int j = 0; j < nAK5Jet; j++)
      {
         double PT2 = pxAK5Jet[j] * pxAK5Jet[j] + pyAK5Jet[j] * pyAK5Jet[j];
         if(PT2 < 40 * 40)
            continue;
         if(etaAK5Jet[j] < -3 || etaAK5Jet[j] > 3)
            continue;

         Jets.push_back(FourVector(energyAK5Jet[j], pxAK5Jet[j], pyAK5Jet[j], pzAK5Jet[j]));
      }
      if(Jets.size() > 20)
      {
         cout << "More than 20 jets!!!  Skip for now...." << endl;
         continue;
      }
      vector<FourVector> Groups = SplitIntoGroups(Jets, true);

      FourVector MET(0, pxMet[0], pyMet[0], 0);
      MET[0] = MET.GetP();

      MR = GetMR(Groups[0], Groups[1]);
      R = GetR(Groups[0], Groups[1], MET);

      vector<float> TCHEValues;
      vector<float> TCHPValues;
      vector<float> SSVHEValues;
      vector<float> SSVHPValues;
      for(int j = 0; j < nAK5Jet; j++)
      {
         double PT2 = pxAK5Jet[j] * pxAK5Jet[j] + pyAK5Jet[j] * pyAK5Jet[j];
         if(PT2 < 40 * 40)
            continue;
         if(etaAK5Jet[j] < -2.4 || etaAK5Jet[j] > 2.4)   // not in the b-tag range
            continue;

         TCHEValues.push_back(TCHE[j]);
         TCHPValues.push_back(TCHP[j]);
         SSVHEValues.push_back(SSVHE[j]);
         SSVHPValues.push_back(SSVHP[j]);
      }

      sort(TCHEValues.begin(), TCHEValues.end(), greater<float>());
      sort(TCHPValues.begin(), TCHPValues.end(), greater<float>());
      sort(SSVHEValues.begin(), SSVHEValues.end(), greater<float>());
      sort(SSVHPValues.begin(), SSVHPValues.end(), greater<float>());

      if(TCHEValues.size() > 0)    MaxTCHE = TCHEValues[0];
      if(TCHEValues.size() > 1)    SecondMaxTCHE = TCHEValues[1];
      if(TCHPValues.size() > 0)    MaxTCHP = TCHPValues[0];
      if(TCHPValues.size() > 1)    SecondMaxTCHP = TCHPValues[1];
      if(SSVHEValues.size() > 0)   MaxSSVHE = SSVHEValues[0];
      if(SSVHEValues.size() > 1)   SecondMaxSSVHE = SSVHEValues[1];
      if(SSVHPValues.size() > 0)   MaxSSVHP = SSVHPValues[0];
      if(SSVHPValues.size() > 1)   SecondMaxSSVHP = SSVHPValues[1];

      OutputTree.Fill();
   }

   OutputTree.Write();
   F.Close();
}

bool CheckBit(int firedTrg[], int bit)
{
   if(bit < 0)
      return false;

   int block = bit / 30;
   int pos = bit % 30;
   int word = firedTrg[block];

   if(!((word >> pos) % 2))
      return false;
   return true;
}





