#include <iostream>
#include <algorithm>
#include <functional>
// using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CustomAssert.h"
#include "CommandLine.h"

#include "Messenger.h"

#include "RhoCalculator.h"

int main(int argc, char *argv[]);
std::vector<double> CalculateRho(PFTreeMessenger &MPF);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   std::string InputFileName = CL.Get("input");

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

      std::vector<double> Rho = CalculateRho(MPF);

      std::cout << "Event: " << iE << "/" << EntryCount << std::endl;
      for(int i = 0; i < (int)Rho.size(); i++)
         std::cout << " " << i << "=" << Rho[i];
      std::cout << std::endl;
   }

   InputFile.Close();

   return 0;
}

std::vector<double> CalculateRho(PFTreeMessenger &MPF)
{
   int N = MPF.ID->size();
   std::vector<FourVector> PF(N);

   for(int i = 0; i < N; i++)
   {
      PF[i].SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
      PF[i][0] = (*MPF.E)[i];
   }

   RhoCalculator Calculator;
   Calculator.SetCMSPreset();
   return Calculator.CalculateRho(PF);
}


