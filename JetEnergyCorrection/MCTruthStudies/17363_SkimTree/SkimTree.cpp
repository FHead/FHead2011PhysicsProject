#include <iostream>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   double PTMin = CL.GetDouble("ptmin", 20);
   double PTMax = CL.GetDouble("ptmax", 1000);
   double EtaMin = CL.GetDouble("etamin", -5.2);
   double EtaMax = CL.GetDouble("etamax", 5.2);
   double RhoMin = CL.GetDouble("rhomin", 0);
   double RhoMax = CL.GetDouble("rhomax", 1000);
   string InputFileName = CL.Get("input");
   string InputTree = CL.Get("tree", "Tree");
   string OutputFileName = CL.Get("output", "Skimmed.root");
   double Fraction = CL.GetDouble("fraction", 1.00);

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get(InputTree.c_str());

   if(Tree == NULL)
      return -1;

   long long Run, Lumi, Event, NPV;
   float Rho, GenPT, GenEta, GenPhi, JetPT, JetEta, JetPhi, JetPTL1, JetPTL123, JetArea;
   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Lumi", &Lumi);
   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("NPV", &NPV);
   Tree->SetBranchAddress("Rho", &Rho);
   Tree->SetBranchAddress("GenPT", &GenPT);
   Tree->SetBranchAddress("GenEta", &GenEta);
   Tree->SetBranchAddress("GenPhi", &GenPhi);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetPTL1", &JetPTL1);
   Tree->SetBranchAddress("JetPTL123", &JetPTL123);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("JetArea", &JetArea);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   
   TTree OutputTree("Tree", "Skimmed tree");
   OutputTree.Branch("Run", &Run, "Run/L");
   OutputTree.Branch("Lumi", &Lumi, "Lumi/L");
   OutputTree.Branch("Event", &Event, "Event/L");
   OutputTree.Branch("NPV", &NPV, "NPV/L");
   OutputTree.Branch("Rho", &Rho, "Rho/F");
   OutputTree.Branch("GenPT", &GenPT, "GenPT/F");
   OutputTree.Branch("GenEta", &GenEta, "GenEta/F");
   OutputTree.Branch("GenPhi", &GenPhi, "GenPhi/F");
   OutputTree.Branch("JetPT", &JetPT, "JetPT/F");
   OutputTree.Branch("JetPTL1", &JetPTL1, "JetPTL1/F");
   OutputTree.Branch("JetPTL123", &JetPTL123, "JetPTL123/F");
   OutputTree.Branch("JetEta", &JetEta, "JetEta/F");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi/F");
   OutputTree.Branch("JetArea", &JetArea, "JetArea/F");

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   int Mod = EntryCount / 300;
   if(Mod < 1)   Mod = 1;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Bar.Update(iE);
      Bar.PrintWithMod(Mod);

      if(Rho < RhoMin)      continue;
      if(Rho > RhoMax)      continue;
      if(GenPT < PTMin)     continue;
      if(GenPT > PTMax)     continue;
      if(GenEta < EtaMin)   continue;
      if(GenEta > EtaMax)   continue;

      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}


