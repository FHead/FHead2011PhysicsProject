#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"

#include "JetCorrector.h"

int main(int argc, char *argv[])
{
   JetCorrector JMCJER("Autumn18_V7_MC_PtResolution_AK4PFchs.txt");
   JetCorrector JJERSF("Autumn18_V7_MC_SF_AK4PFchs_Test.txt");
   JetCorrector JDataJER("Autumn18_V7_Data_PtResolution_AK4PFchs.txt");

   TFile File("Result.root", "RECREATE");

   TTree Tree("Tree", "Tree");

   double PT, Eta, Rho;
   Tree.Branch("PT", &PT, "PT/D");
   Tree.Branch("Eta", &Eta, "Eta/D");
   Tree.Branch("Rho", &Rho, "Rho/D");

   double MCJER, JERSF, DataJER;
   Tree.Branch("MCJER", &MCJER, "MCJER/D");
   Tree.Branch("JERSF", &JERSF, "JERSF/D");
   Tree.Branch("DataJER", &DataJER, "DataJER/D");

   for(int i = 0; i < 100000; i++)
   {
      PT = DrawRandom(0, 1000);
      Eta = DrawRandom(-4, 4);
      Rho = DrawRandom(0, 50);

      JMCJER.SetJetPT(PT);
      JMCJER.SetJetEta(Eta);
      JMCJER.SetRho(Rho);
      JJERSF.SetJetPT(PT);
      JJERSF.SetJetEta(Eta);
      JJERSF.SetRho(Rho);
      JDataJER.SetJetPT(PT);
      JDataJER.SetJetEta(Eta);
      JDataJER.SetRho(Rho);

      MCJER = JMCJER.GetCorrection();
      JERSF = JJERSF.GetCorrection();
      DataJER = JDataJER.GetCorrection();

      Tree.Fill();
   }

   Tree.Write();

   File.Close();

   return 0;
}



