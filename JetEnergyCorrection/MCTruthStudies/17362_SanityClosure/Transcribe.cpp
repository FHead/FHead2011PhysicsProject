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

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string L1FileName = CL.Get("l1");
   string L2L3FileName = CL.Get("l2l3");
   string InputTreeName = CL.Get("tree", "ak4pfchs/t");

   JetCorrector L1Corrector(L1FileName);
   JetCorrector L2L3Corrector(L2L3FileName);

   TFile InputFile(InputFileName.c_str());

   TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());
   assert(InputTree != NULL);

   long long npv, run, lumi, evt;
   float rho;
   vector<float> *refpt = 0, *refeta = 0, *refphi = 0;
   vector<float> *jtpt = 0, *jteta = 0, *jtphi = 0, *jtarea = 0;

   InputTree->SetBranchAddress("npv", &npv);
   InputTree->SetBranchAddress("run", &run);
   InputTree->SetBranchAddress("lumi", &lumi);
   InputTree->SetBranchAddress("evt", &evt);
   InputTree->SetBranchAddress("rho", &rho);
   InputTree->SetBranchAddress("refpt", &refpt);
   InputTree->SetBranchAddress("refeta", &refeta);
   InputTree->SetBranchAddress("refphi", &refphi);
   InputTree->SetBranchAddress("jtpt", &jtpt);
   InputTree->SetBranchAddress("jteta", &jteta);
   InputTree->SetBranchAddress("jtphi", &jtphi);
   InputTree->SetBranchAddress("jtarea", &jtarea);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Simple tree with necessary information for closure studies");

   float GenPT, GenEta, GenPhi, JetPT, JetEta, JetPhi, JetArea, JetPTL1, JetPTL123;

   OutputTree.Branch("Run", &run, "Run/L");
   OutputTree.Branch("Lumi", &lumi, "Lumi/L");
   OutputTree.Branch("Event", &evt, "Event/L");
   OutputTree.Branch("NPV", &npv, "NPV/L");
   OutputTree.Branch("Rho", &rho, "Rho/F");
   OutputTree.Branch("GenPT", &GenPT, "GenPT/F");
   OutputTree.Branch("GenEta", &GenEta, "GenEta/F");
   OutputTree.Branch("GenPhi", &GenPhi, "GenPhi/F");
   OutputTree.Branch("JetPT", &JetPT, "JetPT/F");
   OutputTree.Branch("JetPTL1", &JetPTL1, "JetPTL1/F");
   OutputTree.Branch("JetPTL123", &JetPTL123, "JetPTL123/F");
   OutputTree.Branch("JetEta", &JetEta, "JetEta/F");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi/F");
   OutputTree.Branch("JetArea", &JetArea, "JetArea/F");

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      for(int i = 0; i < (int)refpt->size(); i++)
      {
         if((*refpt)[i] < 20)
            continue;

         GenPT = (*refpt)[i];
         GenEta = (*refeta)[i];
         GenPhi = (*refphi)[i];
         
         JetPT = (*jtpt)[i];
         JetEta = (*jteta)[i];
         JetPhi = (*jtphi)[i];
         JetArea = (*jtarea)[i];

         L1Corrector.SetJetPT(JetPT);
         L1Corrector.SetJetEta(JetEta);
         L1Corrector.SetJetPhi(JetPhi);
         L1Corrector.SetJetArea(JetArea);
         L1Corrector.SetRho(rho);

         JetPTL1 = L1Corrector.GetCorrectedPT();

         L2L3Corrector.SetJetPT(JetPTL1);
         L2L3Corrector.SetJetEta(JetEta);
         L2L3Corrector.SetJetPhi(JetPhi);
         L2L3Corrector.SetJetArea(JetArea);
         L2L3Corrector.SetRho(rho);

         JetPTL123 = L2L3Corrector.GetCorrectedPT();
      }

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}




