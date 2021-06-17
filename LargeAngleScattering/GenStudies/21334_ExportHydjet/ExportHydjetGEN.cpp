#include <iostream>
#include <fstream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   int MaxEvent = CL.GetInt("MaxEvent", 100);

   ofstream OutputFile(OutputFileName);

   TFile *File = TFile::Open(InputFileName.c_str());
   Assert(File != NULL, "Input file error");

   TTree *Tree = (TTree *)File->Get("HiGenParticleAna/hi");
   Assert(Tree != NULL, "Input tree not found");

   vector<float> *PT = nullptr, *Eta = nullptr, *Phi = nullptr;
   vector<int> *PDG = nullptr, *SubEvent = nullptr;

   Tree->SetBranchAddress("pt", &PT);
   Tree->SetBranchAddress("eta", &Eta);
   Tree->SetBranchAddress("phi", &Phi);
   Tree->SetBranchAddress("pdg", &PDG);
   Tree->SetBranchAddress("sube", &SubEvent);

   int EntryCount = Tree->GetEntries();

   for(int iE = 0; iE < EntryCount && iE < MaxEvent; iE++)
   {
      Tree->GetEntry(iE);

      OutputFile << "# Event " << iE << endl;
      for(int iP = 0; iP < (int)PT->size(); iP++)
      {
         FourVector P;
         P.SetPtEtaPhi((*PT)[iP], (*Eta)[iP], (*Phi)[iP]);
         OutputFile << P[1] << " " << P[2] << " " << P[3] << " " << 0
            << " " << (*PDG)[iP] << " " << (*SubEvent)[iP] << endl;
      }
      OutputFile << "end" << endl;
   }

   File->Close();
   delete File;

   OutputFile.close();

   return 0;
}


