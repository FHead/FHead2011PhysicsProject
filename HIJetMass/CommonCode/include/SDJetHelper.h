#include <iostream>
#include <vector>

#include "Code/TauHelperFunctions3.h"

// #include "include/Messenger.h"

class JetTreeMessenger;

class SDJetHelper
{
public:
   std::vector<FourVector> RecoSubJet1, RecoSubJet2;
   std::vector<bool> GoodRecoSubJet;
   std::vector<double> RecoSubJetDR;
public:
   std::vector<FourVector> GenSubJet1, GenSubJet2;
   std::vector<bool> GoodGenSubJet;
   std::vector<double> GenSubJetDR;
public:
   std::vector<double> SubJetMaxDR;   // gen-reco matching quality
   std::vector<double> SubJetSumDR;   // gen-reco matching quality
   std::vector<int> Region;   // event categorization
   std::vector<double> SubJetX1;   // sub jet 1 location
   std::vector<double> SubJetY1;   // sub jet 1 location
   std::vector<double> SubJetX2;   // sub jet 2 location
   std::vector<double> SubJetY2;   // sub jet 2 location
   std::vector<double> GenWeightedX;   // PT-weighted location of gen sub jet
   std::vector<double> AverageX;   // PT-weighted location of reco sub jet
   std::vector<double> AverageY;   // PT-weighted location of reco sub jet
   std::vector<bool> Inside;   // whether sub jet 2 is within reach of gen sub jets
public:
   SDJetHelper(JetTreeMessenger &MJet);
   ~SDJetHelper();
   bool Initialize(JetTreeMessenger &MJet);
};




