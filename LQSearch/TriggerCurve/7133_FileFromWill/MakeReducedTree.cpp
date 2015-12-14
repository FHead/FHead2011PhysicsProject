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
   Tree.AddFile("default_MC.root");

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

   bool PassR014MR150BTag;
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

   OutputTree.Branch("PassR014MR150BTag", &PassR014MR150BTag, "PassR014MR150BTag/O");
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

      int R014MR150IndexBTag = -1;

      for(int j = 0; j < nHLT; j++)
         if((*nameHLT)[j].find("R014_MR150_CentralJet40_BTagIP") != string::npos)
            R014MR150IndexBTag = indexHLT[j];

      PassR014MR150BTag = CheckBit(firedTrg, R014MR150IndexBTag);

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





