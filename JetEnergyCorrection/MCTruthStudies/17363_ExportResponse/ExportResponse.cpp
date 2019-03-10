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
   string OutputFileName = CL.Get("output", "Response.txt");
   double Fraction = CL.GetDouble("fraction", 1.00);

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get(InputTree.c_str());

   if(Tree == NULL)
      return -1;

   float Rho, GenPT, GenEta, GenPhi, JetPT, JetEta, JetPhi, JetPTL1, JetPTL123, JetArea;
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

   ofstream out(OutputFileName.c_str());

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

      out << GenPT << " " << JetPT << " " << JetPTL1 << " " << JetPTL123 << endl;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   out.close();

   InputFile.Close();

   return 0;
}


