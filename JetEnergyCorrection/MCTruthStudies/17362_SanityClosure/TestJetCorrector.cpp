#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"

#include "JetCorrector.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string L1FileName = CL.Get("l1");
   string L2L3FileName = CL.Get("l2l3");
   string InputTreeName = CL.Get("tree", "ak4pfchs/t");
   double PT = CL.GetDouble("pt");
   double Eta = CL.GetDouble("eta");
   double Phi = CL.GetDouble("phi", 0);
   double Area = CL.GetDouble("area", 0.4 * 0.4 * M_PI);
   double Rho = CL.GetDouble("rho");

   JetCorrector L1Corrector(L1FileName);
   JetCorrector L2L3Corrector(L2L3FileName);

   L1Corrector.SetJetPT(PT);
   L1Corrector.SetJetEta(Eta);
   L1Corrector.SetJetPhi(Phi);
   L1Corrector.SetJetArea(Area);
   L1Corrector.SetRho(Rho);

   double JetPTL1 = L1Corrector.GetCorrectedPT();

   L2L3Corrector.SetJetPT(JetPTL1);
   L2L3Corrector.SetJetEta(Eta);
   L2L3Corrector.SetJetPhi(Phi);
   L2L3Corrector.SetJetArea(Area);
   L2L3Corrector.SetRho(Rho);

   double JetPTL123 = L2L3Corrector.GetCorrectedPT();

   cout << PT << " " << JetPTL1 << " " << JetPTL123 << endl;

   return 0;
}




