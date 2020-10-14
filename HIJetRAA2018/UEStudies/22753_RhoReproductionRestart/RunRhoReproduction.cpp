#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
using namespace fastjet;

#include "Code/TauHelperFunctions3.h"
#include "CustomAssert.h"
#include "CommandLine.h"

#include "Messenger.h"

#include "RhoCalculator.h"

int main(int argc, char *argv[]);
vector<double> CalculateRho(PFTreeMessenger &MPF);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");

   TFile InputFile(InputFileName.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   PFTreeMessenger MPF(InputFile);

   Assert(MHiEvent.Tree != nullptr, "Error getting HiEvent tree");
   Assert(MPF.Tree != nullptr, "Error getting PF tree");

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MPF.GetEntry(iE);

      vector<double> Rho = CalculateRho(MPF);

      cout << "Event: " << iE << "/" << EntryCount << endl;
      for(int i = 0; i < (int)Rho.size(); i++)
         cout << "   " << i << " " << Rho[i] << endl;
      cout << endl;

      break;
   }

   InputFile.Close();

   return 0;
}

vector<double> CalculateRho(PFTreeMessenger &MPF)
{
   int N = MPF.ID->size();
   vector<FourVector> PF(N);

   for(int i = 0; i < N; i++)
   {
      PF[i].SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
      PF[i][0] = (*MPF.E)[i];
   }

   RhoCalculator Calculator;
   return Calculator.CalculateRho(PF);
}


