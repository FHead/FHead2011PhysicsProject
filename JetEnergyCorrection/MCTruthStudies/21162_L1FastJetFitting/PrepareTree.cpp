#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string InputTreeName = CL.Get("tree", "OutputTree");
   string OutputFileName = CL.Get("output");

   double EtaMin = CL.GetDouble("EtaMin");
   double EtaMax = CL.GetDouble("EtaMax");
   double RecoDRCut = CL.GetDouble("RecoDRCut", 0.05);
   double PTHatMin = CL.GetDouble("PTHatMin", 0);
   double PTHatMax = CL.GetDouble("PTHatMax", 1000);

   double PUPT, Rho, OOA, RefPT, RefEta, RecoDR, Weight, PTHat;

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "recreate");

   TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());
   Assert(InputTree != NULL, "Problem getting input tree");

   InputTree->SetBranchAddress("PUPT", &PUPT);
   InputTree->SetBranchAddress("Rho", &Rho);
   InputTree->SetBranchAddress("OOA", &OOA);
   InputTree->SetBranchAddress("RefPT", &RefPT);
   InputTree->SetBranchAddress("RefEta", &RefEta);
   InputTree->SetBranchAddress("RecoDR", &RecoDR);
   InputTree->SetBranchAddress("Weight", &Weight);
   InputTree->SetBranchAddress("PTHat", &PTHat);

   double OOAPT;

   TTree OutputTree("FitData", "FitData");
   OutputTree.Branch("PT", &PUPT, "PT/D");
   OutputTree.Branch("Rho", &Rho, "Rho/D");
   OutputTree.Branch("OOA", &OOA, "OOA/D");
   OutputTree.Branch("OOAPT", &OOAPT, "OOAPT/D");
   OutputTree.Branch("W", &Weight, "W/D");
   OutputTree.Branch("RefPT", &RefPT, "RefPT/D");

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      if(RefEta < EtaMin)
         continue;
      if(RefEta > EtaMax)
         continue;
      if(RecoDR > RecoDRCut)
         continue;
      if(PTHat < PTHatMin)
         continue;
      if(PTHat > PTHatMax)
         continue;

      OOAPT = OOA / PUPT;
      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}



